//
//  axGraphicInterface.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-02-17.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#pragma once

#include "Util.hpp"

namespace ax {
namespace GL {
	void Resize(const ax::Size& size);

	void Init();

	void Draw(const ax::Size& size);

	void BlockDrawing(const ax::Rect& absRect, const ax::Rect& showRect, const ax::Size& frameSize);

	void UnBlockDrawing();
}
}

// namespace axGraphicInterface
//{
//    void Resize(const ax::Size& size);
//    void Init();
//    void Draw(const ax::Size& size);
//}
