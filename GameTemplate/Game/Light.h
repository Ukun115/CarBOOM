#pragma once


namespace nsCARBOOM
{
	//�f�B���N�V�������C�g�\���̂̐錾
	struct DirLigData {

		Vector3 dirDirection;	//����
		float pad1 = 0.0f;				//HLSL���̒萔�o�b�t�@��float3�^(12��)�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����A���ߍ��킹�����Ă����B
		Vector3 dirColor;		//�F
		float pad2 = 0.0f;				//�p�f�B���O
	};


	//�|�C���g���C�g�\���̂̐錾
	struct PoiLigData {

		Vector3 ptPosition;		//�ʒu
		float pad = 0.0f;				//�p�f�B���O
		Vector3 ptColor;		//�F
		float ptRange = 0.0f;			//�e���͈�
	};


	//�X�|�b�g���C�g�\���̂̐錾
	struct SpotLigData {

		Vector3 spPosition;		//�ʒu
		float pad = 0.0f;				//�p�f�B���O
		Vector3 spColor;		//�F
		float spRange = 0.0f;			//�e���͈�
		Vector3 spDirection;	//�ˏo����
		float spAngle = 0.0f;			//�ˏo�p�x
	};


	//�������C�g�\���̂̐錾
	struct HemiSphereLight
	{
		Vector3 hemiGroundColor;	//�n�ʐF�i�Ƃ�Ԃ��̃��C�g�j
		float pad1 = 0.0f;				//�p�f�B���O
		Vector3 hemiSkyColor;		//�V���F
		float pad2 = 0.0f;				//�p�f�B���O
		Vector3 hemiGroundNormal;	//�n�ʂ̖@��
		float pad3 = 0.0f;				//�p�f�B���O
	};


	//���C�g�S�̂̃f�[�^�\���̂̐錾
	struct ligData {

		DirLigData  dirLigData;					//�f�B���N�V�������C�g�\���̃f�[�^
		PoiLigData  poiLigData[12];				//�|�C���g���C�g�\���̃f�[�^
		SpotLigData spotLigData;				//�X�|�b�g���C�g�\���̃f�[�^
		HemiSphereLight hemiSphereLigData;		//�������C�g�\���̃f�[�^

		Vector3 eyePos;				//���_�̈ʒu
		//Vector3 ambientLight;		//����
	};


	class Light : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		ligData m_ligData;		//���C�g�\���̂̃f�[�^���쐬


		bool Start()override final;
		~Light()override final;
		void Update()override final;


	public:

		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		//�f�B���N�V�������C�g�̕���,�F��ݒ肷��֐�
		void SetDirectionLightData();
		//�|�C���g���C�g�̍��W,�F,�e���͈͂�ݒ肷��֐�
		void SetPointLightData(const Vector3 position, const Vector3 color, const float range, const int lignum);
		//�X�|�b�g���C�g�̍��W,�F,����,�ˏo�͈�,�ˏo�p�x��ݒ肷��֐�
		void SetSpotLightData();
		//�������C�g�̒n�ʐF�i�Ƃ�Ԃ��̃��C�g�j,�V���F,�n�ʂ̖@����ݒ肷��֐�
		void SetHemiSphereLightData();


		/// <summary>
		/// �Q�b�^�[
		/// </summary>
		//���C�g�̃f�[�^���擾����֐�
		ligData GetLight()const { return m_ligData; }
		//���C�g�̃f�[�^�̃A�h���X���擾����֐�
		ligData* GetLightAdoress() { return &m_ligData; }
	};
}