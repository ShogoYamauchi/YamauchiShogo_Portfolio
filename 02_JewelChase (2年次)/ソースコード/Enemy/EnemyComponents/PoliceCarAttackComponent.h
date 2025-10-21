//--------------------------------------------------------------------
// �t�@�C�����FPoliceCarAttackComponent.h
// �T�v�@�@�@�F�p�g�J�[�𐧌䂷��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/01/26	�N���X�̍쐬 
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackComponent.h"
#include "PoliceCarAttackComponent.generated.h"

// �O���錾
class APoliceCar_Warning;
class UBoxComponent;
class USoundBase;
class USEManager;

UCLASS()
class PROTOTYPE_API UPoliceCarAttackComponent : public UEnemyAttackComponent
{
	GENERATED_BODY()
protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UPoliceCarAttackComponent();
	// ���t���[������
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// �e�G�̍U�����Ăяo���֐�
	void EnemyAttack(float _deltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APoliceCar_Warning> _policeCar_WarningClass;	// �e�̐ݒ� (BP������eActor�̎w��)

	UPROPERTY()
	USEManager* _seManager;		// �T�E���h�}�l�[�W���[�C���X�^���X���擾

	UPROPERTY(EditAnywhere)
	USoundBase* _warningSound;		// �p�g�J�[�̓o�ꉹ
	UPROPERTY(EditAnywhere)
	USoundBase* _sirenSound;		// �p�g�J�[�̃T�C������

	//UPROPERTY()
	AActor* _owner;	// �I�[�i�[�̃A�N�^�[

	UPROPERTY()
	UBoxComponent* _pBoxCollisionComponent;		// UE�ō쐬����Box�R���W�����R���|�[�l���g�̊i�[�p 

	UPROPERTY(EditAnywhere)
	FVector _warningActorSpawnLocation;	// �x�����o���ʒu
	UPROPERTY()
	FVector _initialLocation;			// �����ʒu
	UPROPERTY(EditAnywhere)
	FVector _forwardTargetLocation;		// �O���̒�ʒu�̏ꏊ�i�X�|�[�������ꏊ���瑫�����̒l�j

	UPROPERTY(EditAnywhere)
	float _appearStartTime;	// �o�ꂵ�����܂ł̎���
	UPROPERTY(EditAnywhere)
	float _appearDuration;	// �o��ɂ����鎞��
	UPROPERTY(EditAnywhere)
	float _exitStartTime;	// �ޏꂵ�����܂ł̎���
	UPROPERTY(EditAnywhere)
	float _exitMoveSpeed;	// �ޏꂷ��ۂ̃X�s�[�h
	UPROPERTY(EditAnywhere)
	float _exitDuration;	// �ޏ�ɂ����鎞��

	FVector _appearTargetLocation;	// �o�ꂷ��ۂ̖ڕW�ʒu

	float _currentSpeed;	// ���݂̈ړ����x
	float _timer;			// �^�C�}�[(���\�^�C�}�[)
	float _exitTimer;		// �^�C�}�[(�ޏ�p�^�C�}�[)
	float _appearTimer;		// �^�C�}�[(�o��p�̃^�C�}�[)

	bool _isAppear;	// �o�ꂵ�����ǂ����̃t���O
	bool _isSound;	// �T�E���h��炵�����ǂ����̃t���O�@�Ë�����

	// �ړI�n�܂ňړ����Ȃ���o�ꂳ����֐�
	void _appearAtLocation(float deltaTime);
	// ��ނ����đޏꂳ����֐�
	void _moveBackAndExit(float deltaTime);
};
