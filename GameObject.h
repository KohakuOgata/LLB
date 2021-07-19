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
	/// 自分のインスタンスを削除する時に呼び出す
	/// 次回のUpdateの前に削除される
	/// </summary>
	void DestroyMe() { destroyFlag = true; }

	/// <summary>
	/// インスタンスが削除要求されているかを調べる
	/// 主に、SceneManagerでチェックしている
	/// </summary>
	/// <returns></returns>
	bool IsDestroy() const { return destroyFlag; }

	/// <summary>
	/// タグをつける
	/// タグは１つだけ付けることができます
	/// </summary>
	/// <param name="_tag">タグ</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// 指定されたタグと同じかを返す
	/// </summary>
	/// <param name="_tag">タグ</param>
	/// <returns>同じであればtrue</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }

	/// <summary>
	/// タグを取得する
	/// </summary>
	/// <returns>設定されているタグ</returns>
	const std::string& GetTag() const { return tag; }

	/// <summary>
	/// 所属するシーンを返す
	/// </summary>
	/// <returns>所属するシーンのポインター</returns>
	SceneBase* GetScene() const { return pScene; }

	/// <summary>
	/// シーンのポインターを保存する
	/// </summary>
	/// <returns>所属するシーンのポインター</returns>
	void SetScene(SceneBase* _scene) { pScene = _scene; }

	/// <summary>
	/// 親のオブジェクトを返す
	/// </summary>
	/// <returns>親オブジェクトのポインター</returns>
	GameObject* GetParent() const { return Parent; }

	/// <summary>
	/// 親のオブジェクトを返す
	/// </summary>
	/// <returns>親オブジェクトのポインター</returns>
	void SetParent(GameObject* _parent) { Parent = _parent; }
private:
	SceneBase* pScene;   // 所属するシーン
	GameObject* Parent; // 親のオブジェクト
	bool destroyFlag;        // 自分を削除するか否か
	std::string tag;     // タグ
};
