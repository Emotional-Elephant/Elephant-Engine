#include "Vehicle.h"
#include "SteeringBehaviors.h"

void Vehicle::Update(float time_elapsed)
{
	/*Vector2D SteeringForce = _pSteering->Calculate();
	Vector2D acceleration = SteeringForce / _fMass;
	_vVelocity += acceleration * time_elapsed;
	// ��ݱⰡ Ȯ���ϰ� �ִ� �ӵ��� ���� �ʰ� ��
	_vVelocity.Truncate(_fMaxSpeed);

	_vMovingPos += _vVelocity * time_elapsed;

	if (_vVelocity.LengthSq() > 0.00000001)
	{
		_vHeading = _vVelocity.Identity();
		_vSide = _vHeading.Perp();
	}*/
}

Vehicle::Vehicle()
{
	_pSteering = new SteeringBehaviors(this);
}

Vehicle::~Vehicle()
{
}
