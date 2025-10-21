//--------------------------------------------------------------------
// �t�@�C�����FPoliceAttackComponent.h
// �T�v�@�@�@�F�x�@�i�G�j�̍U������R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/03	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "prototype/Interface/IBulletFactory.h"		// �e��ł֐�������C���^�[�t�F�[�X
#include "CoreMinimal.h"
#include "EnemyAttackComponent.h"
#include "PoliceAttackComponent.generated.h"

// �O���錾
class ULineControllerComponent;
class AEnemyBullet;
class USEManager;
class USoundBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UPoliceAttackComponent : public UEnemyAttackComponent, public IBulletFactory
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	UPoliceAttackComponent();
	// ���t���[������
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// �e�G�̍U�����Ăяo���֐�
	void EnemyAttack(float _deltaTime) override;

	UFUNCTION()
	void SpawnBullet();	// �e���C���X�^���X������֐�
	UFUNCTION()
	void DrawPredictionSplineWithCollision(float DeltaTime);	// �\�������o���֐�

	// �U���͂��擾����֐�
	int GetAttackPower()const { return _policeAttackPower; }

	// �x�@�̏�Ԃ��擾���邽�߂̊֐�
	UFUNCTION(BlueprintCallable, Category = "MyDunctions")
	EnemyStatus GetPoliceStatus()const { return EnemyState; }
	// ���ˊԊu���擾����֐�
	UFUNCTION(BlueprintCallable)
	float GetTimeToFire() { return _timeToFire; }
	// �U���\���ǂ����̃t���O���擾����֐�
	UFUNCTION(BlueprintCallable)
	bool GetAttackAbleFlag() { return _isAttackAble; }

	// �Ë�����
	UFUNCTION(BlueprintCallable)
	AActor* GetPoliceActor() { return _owner; }

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyBullet> _enemyBulletActor;	// �e�̐ݒ� (BP������eActor�̎w��)

	UPROPERTY()
	TArray<AActor*> _pItems;	// �A�C�e�����ׂāi�W���G���E�}�O�l�b�g�E�񕜁j�i�[�p
	UPROPERTY()
	TArray<AActor*> _pSmogs;	// ���i�[�p

	UPROPERTY()
	USEManager* _seManager;			// �T�E���h�}�l�[�W���[

	UPROPERTY(EditAnywhere)
	USoundBase* _gunSound;			// �x�@�̎ˌ���

	UPROPERTY()
	ULineControllerComponent* _pLineControllerComponent;		// �\�������o�����߂̃R���|�[�l���g

	//UPROPERTY()
	AActor* _owner;	// �I�[�i�[�̃A�N�^�[

	UPROPERTY(EditAnywhere)
	FVector _enemyBulletOffset;	// �e�̔��ˈʒu�̃I�t�Z�b�g

	UPROPERTY(EditAnywhere)
	float _bulletSpeed;			// �e�̃X�s�[�h
	UPROPERTY(EditAnywhere)
	float _timeToAttack;		// �X�|�[�����Ă���\�����o���܂ł̎���
	UPROPERTY(EditAnywhere)
	float _enemyAttackCooldown;		// ����ł�����ēx�v���C���[��_������
	UPROPERTY(EditAnywhere)
	float _predictionStopToFireInterval;	// �\�������~�܂��Ă��甭�C����܂ł̎���
	UPROPERTY(EditAnyWhere)
	float _timeToFire;			// ���ˊԊu(����)

	UPROPERTY(EditAnywhere)
	int _policeAttackPower;		// �U����

	FCollisionQueryParams _queryParamsToTrace;		// ��������N�G���p�����[�^�i�g���[�X�p�j

	float _canAttackTimer;	// �^�C�}�[(�o�����Ă���\�������o���܂ł̎��Ԍv��)
	float _bulletTimer;		// �^�C�}�[(�\�������o���Ă��甭�˂���܂ł̎��Ԍv��)
	bool _hasFired;			// ����ł������̃t���O
};
