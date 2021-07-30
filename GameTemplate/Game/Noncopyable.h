#pragma once

namespace nsCARBOOM
{
    class Noncopyable : public IGameObject      // IGameObjectを継承する。
    {
        // デフォルトコンストラクタを使用する。
        Noncopyable() = default;
        // コピーコンストラクタを削除。
        Noncopyable(const Noncopyable& t) = delete;
        // 代入演算子を削除。
        const Noncopyable& operator=(const Noncopyable& t) = delete;
    };
}