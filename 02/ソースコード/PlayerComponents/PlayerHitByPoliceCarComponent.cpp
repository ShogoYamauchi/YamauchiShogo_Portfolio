//--------------------------------------------------------------------
// �t�@�C�����FPlayerHitByPoliceCarComponent.cpp
// �T�v�@�@�@�F�v���C���[���p�g�J�[�ɓ��������ۂɒe���������s�����߂̃R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/02/01	�N���X�̍쐬
//--------------------------------------------------------------------

#include "prototype/Player/PlayerComponent/PlayerHitByPoliceCarComponent.h"

// �R���X�g���N�^
UPlayerHitByPoliceCarComponent::UPlayerHitByPoliceCarComponent()
	: _playerActor(nullptr)
	, _policeCarActor(nullptr)
	, _playerLocation(0.0f,0.0f,0.0f)
	, _relativeLocation(0.0f,0.0f,0.0f)
	, _knockbackDirection(0.0f,0.0f,0.0f)
	, _crossProductZ(0.0f)
	, _timer(0.0f)
	, _playerMaxLocationY(0.0f)
	, _playerMinLocationY(0.0f)
	, _isHitPoliceCar(false)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UPlayerHitByPoliceCarComponent::BeginPlay()
{
	Super::BeginPlay();
}

// ���t���[������
void UPlayerHitByPoliceCarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("_pPlayerHitByPoliceCarComponent Tick"));

	// �t���O���オ��܂œ_�ł�����
	if (_isHitPoliceCar)
	{
		//���Ԍv��
		_timer += DeltaTime;
		if (_timer < _knockbackDuration)
		{
			UE_LOG(LogTemp, Log, TEXT("KnockBacking"));	// �f�o�b�O�p
			_knockBack(DeltaTime);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Knockback is over"));
			_isHitPoliceCar = false;
			//PrimaryComponentTick.bCanEverTick = false;
		}		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("false _isHitPoliceCar"));	
	}
}

// �֐����FClampPlayerYLocation
// �����FplayerMaxLocationY�F�v���C���[��Y���W�̍ő�l, playerMinLocationY�F�v���C���[��Y���W�̍ŏ��l
// �߂�l�F�Ȃ�
// �v���C���[��Y���W�̐����l���擾����֐�
void UPlayerHitByPoliceCarComponent::ClampPlayerYLocation(float playerMaxLocationY, float playerMinLocationY)
{
	// �����l���擾
	_playerMaxLocationY = playerMaxLocationY;
	_playerMinLocationY = playerMinLocationY;
}

// �֐����FTriggerKnockBack
// �����F playerLocation�F�v���C���[�A�N�^�[, policeCarActor�F���������p�g�J�[�A�N�^�[
// �߂�l�F�Ȃ�
// ���e�F�e���̃g���K�[��ON�ɂ���֐�
void UPlayerHitByPoliceCarComponent::TriggerKnockBack(AActor* playerActor, AActor* policeCarActor)
{
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("_isHitPoliceCar ON"));
	_timer = 0.0f;	// �^�C�}�[�̏�����
	_isHitPoliceCar = true;				// �e����t���O��ON

	_playerActor = playerActor;	// �v���C���[�̍��W���擾����
	_policeCarActor = policeCarActor;	// ���������p�g�J�[���擾����
	_calculateKnockbackDirection();		// �m�b�N�o�b�N����������v�Z����
}

// �֐����F_CalculateKnockbackDirection
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�m�b�N�o�b�N����������v�Z����֐�
void  UPlayerHitByPoliceCarComponent::_calculateKnockbackDirection()
{
	if (!_playerActor) { return; }		// �v���C���[�����݂��邩�`�F�b�N
	if (!_policeCarActor) { return; }	// �p�g�J�[�����݂��邩�`�F�b�N

	// �p�g�J�[�̍��W�A�E�����x�N�g�����擾
	FVector _policeCarLocation = _policeCarActor->GetActorLocation();	// �p�g�J�[�̍��W
	FVector _policeCarForwardVector = _policeCarActor->GetActorForwardVector(); // �p�g�J�[�̉E�����x�N�g��

	// �v���C���[�̍��W���擾
	_playerLocation = _playerActor->GetActorLocation();

	// �v���C���[�ƃp�g�J�[�̑��Έʒu���v�Z
	_relativeLocation = _playerLocation - _policeCarLocation;

	// ���Έʒu�ƉE�����x�N�g���̊O�ς��v�Z
	float _crossProduct = FVector::CrossProduct( _policeCarForwardVector, _relativeLocation ).Z;

	// �O�ς�Z�������g���ĉE�������𔻒f
	if (_crossProduct > 0.0f)
	{
		// �O�ς�Z���������Ȃ�A�v���C���[�̓p�g�J�[�́u�����v�ɂ���
		_knockbackDirection = _policeCarActor->GetActorRightVector();	// �E���ɒe��
		UE_LOG(LogTemp, Log, TEXT("knockback direction is RIGHT"));
	}
	else
	{
		// �O�ς�Z���������Ȃ�A�v���C���[�̓p�g�J�[�́u�E���v�ɂ���
		_knockbackDirection = -_policeCarActor->GetActorRightVector();	// �����ɒe��
		UE_LOG(LogTemp, Log, TEXT("knockback direction is LEFT"));
	}

	// �e����ɕǂ�����ꍇ�t�����ɒe��
	if (_isWallInDirection(_playerLocation,_knockbackDirection))
	{
		_knockbackDirection *= -1;
		UE_LOG(LogTemp, Log, TEXT("There was a wall in the knockback direction."));
	}
}

// �֐����F_isWallInDirection
// �����F�v���C���[��e������
// �߂�l�F�t�����ɕς��邩�ǂ����̃t���O (true�F�ς��� / false�F�ς��Ȃ�)
// �e����ɕǂ����邩�m���߂�֐�
bool UPlayerHitByPoliceCarComponent::_isWallInDirection(FVector playerLocation , FVector knockbackDirection)
{
	// �e������̃|�W�V����Y���v�Z
	float _moveTargetLocationY = playerLocation.Y + (knockbackDirection * _knockbackCheckDistancef).Y; // �w�肵�����j�b�g����`�F�b�N

	// �v���C���[�̐����͈͂��o�Ă�����true��Ԃ� 
	return (_moveTargetLocationY < _playerMinLocationY || _moveTargetLocationY > _playerMaxLocationY);
}

// �֐����F_knockBack
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// ���e�F�p�g�J�[�Ƀv���C���[�����������ۂɒe���֐�
void UPlayerHitByPoliceCarComponent::_knockBack(float deltaTime)
{
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("KnockBack execution"));	// �f�o�b�O�p	
	//UE_LOG(LogTemp, Log, TEXT("_knockbackDirection  is : %s"), _knockbackDirection);

	// �m�b�N�o�b�N��̈ʒu���v�Z
	FVector _knockbackTargetLocation = _playerLocation + (_knockbackDirection * _knockBackStrength);

	// ���܂��������Ɏw�肵�������Ńm�b�N�o�b�N������
	_playerActor->SetActorLocation(_knockbackTargetLocation);  // �ǂ𖳎����Ĉړ�
}
