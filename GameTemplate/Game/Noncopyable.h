/// <summary>
/// ノンコピー
/// コピーさせたくないやつに継承させてください。
/// </summary>

#pragma once

namespace myEngine {
	struct Noncopyable {
		Noncopyable() = default;
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}

