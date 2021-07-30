#pragma once

namespace nsCARBOOM
{
    class Noncopyable : public IGameObject      // IGameObject���p������B
    {
        // �f�t�H���g�R���X�g���N�^���g�p����B
        Noncopyable() = default;
        // �R�s�[�R���X�g���N�^���폜�B
        Noncopyable(const Noncopyable& t) = delete;
        // ������Z�q���폜�B
        const Noncopyable& operator=(const Noncopyable& t) = delete;
    };
}