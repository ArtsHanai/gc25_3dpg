#include "IEnemy.h"

void IEnemy::Update()
{
    Actor::Update();
}

void IEnemy::Draw()
{
    Object3D::Draw();
    // カプセル表示
    VECTOR3 p1 = transform.position + capsule.p1;
    VECTOR3 p2 = transform.position + capsule.p2;
	DrawCapsule3D(p1, p2, capsule.rad, 10, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

bool IEnemy::CollideWeapon(Actor* other, VECTOR3 btm, VECTOR3 top)
{
    // カプセルと線分で当てる
    if (capsule.rad == 0.0f)
        return false;
    VECTOR3 p1 = transform.position + capsule.p1;
    VECTOR3 p2 = transform.position + capsule.p2;
    float d = Segment_Segment_MinLength(p1, p2, btm, top);

    if (d < capsule.rad) {
        OnDamage(other);
        return true;
    }
    return false;
}
