#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "macros.h"
#include "types/atomic_types.h"

/***********************************************
What will we need in state_machine (or to be precise: finite state machine)
+ state (obviously)
+ transition(s)
+ event (to trigger state transition, obviously)

goals:
	controller ctrler;
	ctrler.trigger_event(evBackKeyDown);
	ctrler.trigger_event(evForwardKeyDown);
	ctrler.trigger_event(evHighKickKeyDown);
	// trigger skill

automata:
	trigger_event()

events:
	<empty>

states:
	idle -> skill_s1 -> skill_s2 -> skill_s3 (reaction: execute skill)

transition
	trans1<evBackKeyDown, idle, skill_s1>
	trans2<evForwardKeyDown, skill_s1, skill_s2>
	trans3<evHighKickKeyDown, skill_s2, skill_s3>

************************************************/

#endif // __STATE_MACHINE_H__