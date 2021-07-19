#pragma once

enum class InputID : int {
	//キーボード入力定義
	KeyBack = 0x0E,  // バックスペースキー
	KeyTab = 0x0F,  // タブキー
	KeyReturn = 0x1C,  // エンターキー

	KeyLShift = 0x2A,  // 左シフトキー
	KeyRShit = 0x36,  // 右シフトキー
	KeyLControl = 0x1D,  // 左コントロールキー
	KeyRControl = 0x9D,  // 右コントロールキー
	KeyEscape = 0x01,  // エスケープキー
	KeySpace = 0x39,  // スペースキー
	KeyPageUp = 0xC9,  // ＰａｇｅＵＰキー
	KeyPageDown = 0xD1,  // ＰａｇｅＤｏｗｎキー
	KeyEnd = 0xCF,  // エンドキー
	KeyHome = 0xC7,  // ホームキー
	KeyLeft = 0xCB,  // 左キー
	KeyUp = 0xC8,  // 上キー
	KeyRight = 0xCD,  // 右キー
	KeyDown = 0xD0,  // 下キー
	KeyInsert = 0xD2,  // インサートキー
	KeyDelete = 0xD3,  // デリートキー

	KeyMinus = 0x0C,  // －キー
	KeyYen = 0x7D,  // ￥キー
	KeyPrevTrack = 0x90,  // ＾キー
	KeyPeriod = 0x34,  // ．キー
	KeyLAlt = 0x35,  // 左ＡＬＴキー
	KeyRAlt = 0x38,  // 右ＡＬＴキー
	KeySlash = 0xB8,  // ／キー
	KeyScrollLock = 0x46,  // ScrollLockキー
	KeySemicolon = 0x27,  // ；キー
	KeyColon = 0x92,  // ：キー
	KeyLBracket = 0x1A,  // ［キー
	KeyRBracket = 0x1B,  // ］キー
	KeyAt = 0x91,  // ＠キー
	KeyBackSlash = 0x2B,  // ＼キー
	KeyComma = 0x33,  // ，キー
	KeyKanji = 0x94,  // 漢字キー					
	KeyConvert = 0x79,  // 変換キー					
	KeyNoconvert = 0x7B,  // 無変換キー					
	KeyKana = 0x70,  // カナキー					
	KeyApps = 0xDD,  // アプリケーションメニューキー
	KeyCapsLock = 0x3A,  // CaspLockキー
	KeySysrq = 0xB7,  // PrintScreenキー				
	KeyPause = 0xC5,  // PauseBreakキー				
	KeyLwin = 0xDB,  // 左Winキー					
	KeyRwin = 0xDC,  // 右Winキー					

	KeyNumlock = 0x45,  // テンキーNumLockキー	
	KeyNumpad0 = 0x52,  // テンキー０			
	KeyNumpad1 = 0x4F,  // テンキー１			
	KeyNumpad2 = 0x50,  // テンキー２			
	KeyNumpad3 = 0x51,  // テンキー３			
	KeyNumpad4 = 0x4B,  // テンキー４			
	KeyNumpad5 = 0x4C,  // テンキー５			
	KeyNumpad6 = 0x4D,  // テンキー６			
	KeyNumpad7 = 0x47,  // テンキー７			
	KeyNumpad8 = 0x48,  // テンキー８			
	KeyNumpad9 = 0x49,  // テンキー９			
	KeyMultiply = 0x37,  // テンキー＊キー		
	KeyAdd = 0x4E,  // テンキー＋キー		
	KeySubtract = 0x4A,  // テンキー－キー		
	KeyDecimal = 0x53,  // テンキー．キー		
	KeyDivide = 0xB5,  // テンキー／キー		
	KeyNumpadenter = 0x9C,  // テンキーのエンターキー

	KeyF1 = 0x3B,  // Ｆ１キー
	KeyF2 = 0x3C,  // Ｆ２キー
	KeyF3 = 0x3D,  // Ｆ３キー
	KeyF4 = 0x3E,  // Ｆ４キー
	KeyF5 = 0x3F,  // Ｆ５キー
	KeyF6 = 0x40,  // Ｆ６キー
	KeyF7 = 0x41,  // Ｆ７キー
	KeyF8 = 0x42,  // Ｆ８キー
	KeyF9 = 0x43,  // Ｆ９キー
	KeyF10 = 0x44,  // Ｆ１０キー
	KeyF11 = 0x57,  // Ｆ１１キー
	KeyF12 = 0x58,  // Ｆ１２キー

	KeyA = 0x1E,  // Ａキー
	KeyB = 0x30,  // Ｂキー
	KeyC = 0x2E,  // Ｃキー
	KeyD = 0x20,  // Ｄキー
	KeyE = 0x12,  // Ｅキー
	KeyF = 0x21,  // Ｆキー
	KeyG = 0x22,  // Ｇキー
	KeyH = 0x23,  // Ｈキー
	KeyI = 0x17,  // Ｉキー
	KeyJ = 0x24,  // Ｊキー
	KeyK = 0x25,  // Ｋキー
	KeyL = 0x26,  // Ｌキー
	KeyM = 0x32,  // Ｍキー
	KeyN = 0x31,  // Ｎキー
	KeyO = 0x18,  // Ｏキー
	KeyP = 0x19,  // Ｐキー
	KeyQ = 0x10,  // Ｑキー
	KeyR = 0x13,  // Ｒキー
	KeyS = 0x1F,  // Ｓキー
	KeyT = 0x14,  // Ｔキー
	KeyU = 0x16,  // Ｕキー
	KeyV = 0x2F,  // Ｖキー
	KeyW = 0x11,  // Ｗキー
	KeyX = 0x2D,  // Ｘキー
	KeyY = 0x15,  // Ｙキー
	KeyZ = 0x2C,  // Ｚキー
	Key0 = 0x0B,  // ０キー
	Key1 = 0x02,  // １キー
	Key2 = 0x03,  // ２キー
	Key3 = 0x04,  // ３キー
	Key4 = 0x05,  // ４キー
	Key5 = 0x06,  // ５キー
	Key6 = 0x07,  // ６キー
	Key7 = 0x08,  // ７キー
	Key8 = 0x09,  // ８キー
	Key9 = 0x0A,  // ９キー

	//マウス入力定義
	MouseLeft = 0x1001,	// マウス左ボタン
	MouseRight = 0x1002,	// マウス右ボタン
	MouseMiddle = 0x1004,	// マウス中央ボタン
	Mouse1 = 0x1001,	// マウス１ボタン
	Mouse2 = 0x1002,	// マウス２ボタン
	Mouse3 = 0x1004,	// マウス３ボタン
	Mouse4 = 0x1008,	// マウス４ボタン
	Mouse5 = 0x1010,	// マウス５ボタン
	Mouse6 = 0x1020,	// マウス６ボタン
	Mouse7 = 0x1040,	// マウス７ボタン
	Mouse8 = 0x1080,	// マウス８ボタン

	//XInputボタン入力定義
	PadDPadUp = 0x2000,		    // デジタル方向ボタン上
	PadDPadDown,				// デジタル方向ボタン下
	PadDPadLeft,				// デジタル方向ボタン左
	PadDPadRight,			    // デジタル方向ボタン右
	PadStart,				    // STARTボタン
	PadBack,					// BACKボタン
	PadLeftThumbClick,		    // 左スティック押し込み
	PadRightThumbClick,		    // 右スティック押し込み
	PadLeftShoulder,			// LBボタン
	PadRightShoulder,		    // RBボタン
	PadA,					    // Aボタン
	PadB,					    // Bボタン
	PadX,					    // Xボタン
	PadY,					    // Yボタン
	PadLeftThumbTilt,		    // 左スティックいずれかの方向入力
	PadLeftThumbTiltUp,		    // 左スティック上方向入力
	PadLeftThumbTiltDown,	    // 左スティック下方向入力
	PadLeftThumbTiltLeft,	    // 左スティック左方向入力
	PadLeftThumbTiltRight,	    // 左スティック右方向入力
	PadRightThumbTilt,		    // 右スティックいずれかの方向入力
	PadRightThumbTiltUp,		// 右スティック上方向入力
	PadRightThumbTiltDown,	    // 右スティック下方向入力
	PadRightThumbTiltLeft,	    // 右スティック左方向入力
	PadRightThumbTiltRight,	    // 右スティック右方向入力
	PadRightTrigger,            // 右トリガー
	PadLeftTrigger,             // 左トリガー

	Pad1DPadUp = 0x3000,		// パッド1のデジタル方向ボタン上
	Pad1DPadDown,				// パッド1のデジタル方向ボタン下
	Pad1DPadLeft,				// パッド1のデジタル方向ボタン左
	Pad1DPadRight,			    // パッド1のデジタル方向ボタン右
	Pad1Start,				    // パッド1のSTARTボタン
	Pad1Back,					// パッド1のBACKボタン
	Pad1LeftThumbClick,		    // パッド1の左スティック押し込み
	Pad1RightThumbClick,		// パッド1の右スティック押し込み
	Pad1LeftShoulder,			// パッド1のLBボタン
	Pad1RightShoulder,		    // パッド1のRBボタン
	Pad1A,					    // パッド1のAボタン
	Pad1B,					    // パッド1のBボタン
	Pad1X,					    // パッド1のXボタン
	Pad1Y,					    // パッド1のYボタン
	Pad1LeftThumbTilt,		    // パッド1の左スティックいずれかの方向入力
	Pad1LeftThumbTiltUp,		// パッド1の左スティック上方向入力
	Pad1LeftThumbTiltDown,	    // パッド1の左スティック下方向入力
	Pad1LeftThumbTiltLeft,	    // パッド1の左スティック左方向入力
	Pad1LeftThumbTiltRight,	    // パッド1の左スティック右方向入力
	Pad1RightThumbTilt,		    // パッド1の右スティックいずれかの方向入力
	Pad1RightThumbTiltUp,		// パッド1の右スティック上方向入力
	Pad1RightThumbTiltDown,	    // パッド1の右スティック下方向入力
	Pad1RightThumbTiltLeft,	    // パッド1の右スティック左方向入力
	Pad1RightThumbTiltRight,	// パッド1の右スティック右方向入力
	Pad1RightTrigger,           // パッド1右トリガー
	Pad1LeftTrigger,			// パッド1左トリガー

	Pad2DPadUp = 0x4000,		// パッド2のデジタル方向ボタン上
	Pad2DPadDown,				// パッド2のデジタル方向ボタン下
	Pad2DPadLeft,				// パッド2のデジタル方向ボタン左
	Pad2DPadRight,			    // パッド2のデジタル方向ボタン右
	Pad2Start,				    // パッド2のSTARTボタン
	Pad2Back,					// パッド2のBACKボタン
	Pad2LeftThumbClick,		    // パッド2の左スティック押し込み
	Pad2RightThumbClick,		// パッド2の右スティック押し込み
	Pad2LeftShoulder,			// パッド2のLBボタン
	Pad2RightShoulder,		    // パッド2のRBボタン
	Pad2A,					    // パッド2のAボタン
	Pad2B,					    // パッド2のBボタン
	Pad2X,					    // パッド2のXボタン
	Pad2Y,					    // パッド2のYボタン
	Pad2LeftThumbTilt,		    // パッド2の左スティックいずれかの方向入力
	Pad2LeftThumbTiltUp,		// パッド2の左スティック上方向入力
	Pad2LeftThumbTiltDown,	    // パッド2の左スティック下方向入力
	Pad2LeftThumbTiltLeft,	    // パッド2の左スティック左方向入力
	Pad2LeftThumbTiltRight,	    // パッド2の左スティック右方向入力
	Pad2RightThumbTilt,		    // パッド2の右スティックいずれかの方向入力
	Pad2RightThumbTiltUp,		// パッド2の右スティック上方向入力
	Pad2RightThumbTiltDown,	    // パッド2の右スティック下方向入力
	Pad2RightThumbTiltLeft,	    // パッド2の右スティック左方向入力
	Pad2RightThumbTiltRight,	// パッド2の右スティック右方向入力
	Pad2RightTrigger,           // パッド2右トリガー
	Pad2LeftTrigger,			// パッド2左トリガー

	Pad3DPadUp = 0x5000,		// パッド3のデジタル方向ボタン上
	Pad3DPadDown,				// パッド3のデジタル方向ボタン下
	Pad3DPadLeft,				// パッド3のデジタル方向ボタン左
	Pad3DPadRight,			    // パッド3のデジタル方向ボタン右
	Pad3Start,				    // パッド3のSTARTボタン
	Pad3Back,					// パッド3のBACKボタン
	Pad3LeftThumbClick,		    // パッド3の左スティック押し込み
	Pad3RightThumbClick,		// パッド3の右スティック押し込み
	Pad3LeftShoulder,			// パッド3のLBボタン
	Pad3RightShoulder,		    // パッド3のRBボタン
	Pad3A,					    // パッド3のAボタン
	Pad3B,					    // パッド3のBボタン
	Pad3X,					    // パッド3のXボタン
	Pad3Y,					    // パッド3のYボタン
	Pad3LeftThumbTilt,		    // パッド3の左スティックいずれかの方向入力
	Pad3LeftThumbTiltUp,		// パッド3の左スティック上方向入力
	Pad3LeftThumbTiltDown,	    // パッド3の左スティック下方向入力
	Pad3LeftThumbTiltLeft,	    // パッド3の左スティック左方向入力
	Pad3LeftThumbTiltRight,	    // パッド3の左スティック右方向入力
	Pad3RightThumbTilt,		    // パッド3の右スティックいずれかの方向入力
	Pad3RightThumbTiltUp,		// パッド3の右スティック上方向入力
	Pad3RightThumbTiltDown,	    // パッド3の右スティック下方向入力
	Pad3RightThumbTiltLeft,	    // パッド3の右スティック左方向入力
	Pad3RightThumbTiltRight,	// パッド3の右スティック右方向入力
	Pad3RightTrigger,           // パッド3右トリガー
	Pad3LeftTrigger,			// パッド3左トリガー

	Pad4DPadUp = 0x6000,		// パッド4のデジタル方向ボタン上
	Pad4DPadDown,				// パッド4のデジタル方向ボタン下
	Pad4DPadLeft,				// パッド4のデジタル方向ボタン左
	Pad4DPadRight,			    // パッド4のデジタル方向ボタン右
	Pad4Start,				    // パッド4のSTARTボタン
	Pad4Back,					// パッド4のBACKボタン
	Pad4LeftThumbClick,		    // パッド4の左スティック押し込み
	Pad4RightThumbClick,		// パッド4の右スティック押し込み
	Pad4LeftShoulder,			// パッド4のLBボタン
	Pad4RightShoulder,		    // パッド4のRBボタン
	Pad4A,					    // パッド4のAボタン
	Pad4B,					    // パッド4のBボタン
	Pad4X,					    // パッド4のXボタン
	Pad4Y,					    // パッド4のYボタン
	Pad4LeftThumbTilt,		    // パッド4の左スティックいずれかの方向入力
	Pad4LeftThumbTiltUp,		// パッド4の左スティック上方向入力
	Pad4LeftThumbTiltDown,	    // パッド4の左スティック下方向入力
	Pad4LeftThumbTiltLeft,	    // パッド4の左スティック左方向入力
	Pad4LeftThumbTiltRight,	    // パッド4の左スティック右方向入力
	Pad4RightThumbTilt,		    // パッド4の右スティックいずれかの方向入力
	Pad4RightThumbTiltUp,		// パッド4の右スティック上方向入力
	Pad4RightThumbTiltDown,	    // パッド4の右スティック下方向入力
	Pad4RightThumbTiltLeft,	    // パッド4の右スティック左方向入力
	Pad4RightThumbTiltRight,	// パッド4の右スティック右方向入力
	Pad4RightTrigger,           // パッド4右トリガー
	Pad4LeftTrigger,			// パッド4左トリガー
};