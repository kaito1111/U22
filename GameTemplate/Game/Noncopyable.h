/// <summary>
/// �m���R�s�[
/// �R�s�[���������Ȃ���Ɍp�������Ă��������B
/// </summary>

#pragma once

namespace myEngine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}

