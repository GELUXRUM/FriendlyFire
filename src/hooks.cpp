#include "hooks.h"
#include "detourxs/detourxs.h"

namespace HookLineAndSinker
{
	typedef bool(ActorCheckValidTargetSig)(RE::AIProcess**, RE::TESObjectREFR*);
	REL::Relocation<ActorCheckValidTargetSig> OriginalFunction;
	DetourXS hook;

	bool HookedActorCheckValidTarget(RE::AIProcess**, RE::TESObjectREFR*)
	{
		return true;
	}

	void RegisterHook()
	{
		REL::Relocation<ActorCheckValidTargetSig> funcLocation{ REL::ID(1296927) };
		if (hook.Create(reinterpret_cast<LPVOID>(funcLocation.address()), &HookedActorCheckValidTarget)) {
			OriginalFunction = reinterpret_cast<std::uintptr_t>(hook.GetTrampoline());
		} else {
			logger::warn("Failed to create hook");
		}
	}
}
