#pragma once
#include "IEnemy.h"
#include "Animator.h"

class Goblin : public IEnemy {
public:
	Goblin(VECTOR3 pos, float rotY);
	~Goblin();
	void Update() override;
//	void Draw() override;
	void OnDamage(Actor* other) override;
private:
	enum AnimID {
		aNeutral = 0,
		aRun,
		aDamage = 10,
		aBlowIn,
		aBlowLoop,
		aBlowOut,
		aDown,
		aAttack = 20,
	};
	int hp;

	enum State {
		sNormal,
		sDamage,
		sBlow,
		sAttack,
	};
	State state;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateBlow();
	void UpdateAttack();
	int blowAnim;

	VECTOR3 velocity; // 移動ベクトル

	bool InSight(float dist, float ang);

	class StateBase {
	public:
		StateBase(Goblin* gob) { owner = gob; }
		virtual ~StateBase() {}
		virtual bool Update() = 0; // 終わったらtrue
		virtual std::string ID() { return ""; }
	protected:
		Goblin* owner;
	};
	class ActionApproach : public StateBase {
	public:
		ActionApproach(Goblin* gob);
		~ActionApproach();
		bool Update() override;
		std::string ID() override { return "Approach"; }
	};
	class ActionAttack : public StateBase {
	public:
		ActionAttack(Goblin* gob);
		~ActionAttack();
		bool Update() override;
		std::string ID() override { return "Attack"; }
	};
	StateBase* action;
};