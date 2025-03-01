#pragma once

enum CombatActions {
	ATTACK,
	DEFEND
};

enum CombatTargets {
	FRONT_ONE,
	FRONT_TWO,
	FRONT_THREE,
	FRONT_FOUR,
	BACK_ONE,
	BACK_TWO,
	BACK_THREE,
	BACK_FOUR,
};

enum CombatPhases {
	ACTION,
	TARGET,
	PLAYER_WIN,
	PLAYER_LOSS
};

enum Attributes {
	HEALTH,
	DAMAGE,
	SPEED
};
