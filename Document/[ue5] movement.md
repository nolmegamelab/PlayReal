# movement 

## MovementComponent

- EPlaneConstraintAxisSetting
  - 이동을 고정할 축 지정 

- Swept 이동 
  - 충돌을 하면서 물리적으로 이동한다. 
- Sliding 벡터 계산 
- UpdatedComponent를 기준으로 이동 시킨다. 다른 컴포넌트들은 강제로 이동한다. 
  - 보통은 루트 컴포넌트가 UpdatedComponent가 된다. 

- TwoWallAdjust 
  - 구현이 흥미로울 듯. 

언리얼은 실체가 컴포넌트들이다. 폰, 콘트롤러 등은 물리적인 실체가 아닌 논리적인 규칙이나 기능들이다. 
보이고 움직이는 것들은 컴포넌트들이다. 

## UNavMovementComponent 

RequestPathMove() 

경로를 따라 이동하는 기능을 제공한다. 완전한 기능을 제공하지는 못 한다. 
PawnMovementComponent 정도는 되어야 입력을 처리하기위한 추가 정보가 있다. 

실제 콜 스택을 따라가 봐야 하겠다. 

## UCharacterMovementComponent

이동 상태가 추락, 날기, 수영, 걷기 등이 있지만 물리와 연동하여 이동한다. 

https://docs.unrealengine.com/4.26/en-US/BlueprintAPI/AI/Navigation/MovetoLocation/

UAbilityTask_MoveToLocation에 선형 보간을 하면서 이동하는 코드가 잘 정리되어 있다. 

## AIController::MoveTo 

UCharacterMovementComponent와 함께 중요한 예시이다. 이해하고 적절하게 활용한다. 





