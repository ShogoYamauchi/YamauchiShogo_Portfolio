//--------------------------------------------------------------------
// �t�@�C�����FPlayerHitByPoliceCarComponent.h
// �T�v�@�@�@�F�v���C���[���p�g�J�[�ɓ��������ۂɒe���������s�����߂̃R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/02/01	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHitByPoliceCarComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UPlayerHitByPoliceCarComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UPlayerHitByPoliceCarComponent();
	// ���t���[������
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ClampPlayerYLocation(float playerMaxLocationY, float playerMinLocationY);	// �v���C���[��Y���W�̐����l���擾����֐�

	void TriggerKnockBack(AActor* playerActor, AActor* policeCarActor);	// �e���̃g���K�[��ON�ɂ���֐�

private:

	UPROPERTY()
	AActor* _playerActor;  			// �v���C���[�i�[�p
	UPROPERTY()
	AActor* _policeCarActor;		// �p�g�J�[�i�[�p

	UPROPERTY(EditAnywhere)
	FVector _knockBackStrength;		// �e����鋭��
	UPROPERTY(EditAnywhere)
	FVector _offsetPoliceCarPos;	// �p�g�J�[�̈ʒu�����p
	UPROPERTY(EditAnywhere)
	float 	_knockbackEase;			// �m�b�N�o�b�N�̊ɋ}
	UPROPERTY(EditAnywhere)
	float _knockbackCheckDistancef; // �e�������ɕǂ����邩�ǂ����m���߂�ۂ̌v�鋗��
	UPROPERTY(EditAnywhere)
	float _knockbackDuration;		// �m�b�N�o�b�N���s���S�̂̎���

	FVector _playerLocation;		// �v���C���[�̍��W
	FVector _relativeLocation;		// �v���C���[�ƃp�g�J�[�̑��Έʒu
	FVector _knockbackDirection;	// �m�b�N�o�b�N�̕���
	float _crossProductZ;			// �v���C���[�ƃp�g�J�[�̊O��Z����
	float _timer;					// �o�ߎ��ԑ���p
	float _playerMaxLocationY;	// �v���C���[�̍ő�Y���W
	float _playerMinLocationY;	// �v���C���[�̍ő�Y���W
	bool _isHitPoliceCar;			// �p�g�J�[�ɓ����������ǂ����̃t���O

	void _knockBack(float _elapsedTime);	// �p�g�J�[�ɒe�����֐�
	void _calculateKnockbackDirection();	// �m�b�N�o�b�N����������v�Z����֐�
	bool _isWallInDirection(const FVector policeCarLocation);	// �e�������ɕǂ����邩�m���߂�֐�
};