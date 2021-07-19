#pragma once
#include <string>

class SceneBase;

class GameObject
{
public:
	GameObject() : pScene(nullptr), Parent(nullptr), destroyFlag(false), tag("") {}
	GameObject(SceneBase* scene) : pScene(scene), Parent(nullptr), destroyFlag(false), tag("") {}
	GameObject(GameObject* object) : pScene(nullptr), Parent(object), destroyFlag(false), tag("") {}
	GameObject(SceneBase* scene, GameObject* object) : pScene(scene), Parent(object), destroyFlag(false), tag("") {}
	virtual ~GameObject() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void DebugDraw() {}

	/// <summary>
	/// �����̃C���X�^���X���폜���鎞�ɌĂяo��
	/// �����Update�̑O�ɍ폜�����
	/// </summary>
	void DestroyMe() { destroyFlag = true; }

	/// <summary>
	/// �C���X�^���X���폜�v������Ă��邩�𒲂ׂ�
	/// ��ɁASceneManager�Ń`�F�b�N���Ă���
	/// </summary>
	/// <returns></returns>
	bool IsDestroy() const { return destroyFlag; }

	/// <summary>
	/// �^�O������
	/// �^�O�͂P�����t���邱�Ƃ��ł��܂�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// �w�肳�ꂽ�^�O�Ɠ�������Ԃ�
	/// </summary>
	/// <param name="_tag">�^�O</param>
	/// <returns>�����ł����true</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }

	/// <summary>
	/// �^�O���擾����
	/// </summary>
	/// <returns>�ݒ肳��Ă���^�O</returns>
	const std::string& GetTag() const { return tag; }

	/// <summary>
	/// ��������V�[����Ԃ�
	/// </summary>
	/// <returns>��������V�[���̃|�C���^�[</returns>
	SceneBase* GetScene() const { return pScene; }

	/// <summary>
	/// �V�[���̃|�C���^�[��ۑ�����
	/// </summary>
	/// <returns>��������V�[���̃|�C���^�[</returns>
	void SetScene(SceneBase* _scene) { pScene = _scene; }

	/// <summary>
	/// �e�̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g�̃|�C���^�[</returns>
	GameObject* GetParent() const { return Parent; }

	/// <summary>
	/// �e�̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g�̃|�C���^�[</returns>
	void SetParent(GameObject* _parent) { Parent = _parent; }
private:
	SceneBase* pScene;   // ��������V�[��
	GameObject* Parent; // �e�̃I�u�W�F�N�g
	bool destroyFlag;        // �������폜���邩�ۂ�
	std::string tag;     // �^�O
};
