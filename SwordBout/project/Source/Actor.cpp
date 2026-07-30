#include "Actor.h"
#include "Stage.h"

void Actor::CollideStage()
{
	Stage* st = FindGameObject<Stage>();
	if (capsule != nullptr) {
		transform.position += st->CollideCapsule(transform.position, capsule);
	}
}




