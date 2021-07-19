#pragma once

enum class InputID : int {
	//�L�[�{�[�h���͒�`
	KeyBack = 0x0E,  // �o�b�N�X�y�[�X�L�[
	KeyTab = 0x0F,  // �^�u�L�[
	KeyReturn = 0x1C,  // �G���^�[�L�[

	KeyLShift = 0x2A,  // ���V�t�g�L�[
	KeyRShit = 0x36,  // �E�V�t�g�L�[
	KeyLControl = 0x1D,  // ���R���g���[���L�[
	KeyRControl = 0x9D,  // �E�R���g���[���L�[
	KeyEscape = 0x01,  // �G�X�P�[�v�L�[
	KeySpace = 0x39,  // �X�y�[�X�L�[
	KeyPageUp = 0xC9,  // �o�������t�o�L�[
	KeyPageDown = 0xD1,  // �o�������c�������L�[
	KeyEnd = 0xCF,  // �G���h�L�[
	KeyHome = 0xC7,  // �z�[���L�[
	KeyLeft = 0xCB,  // ���L�[
	KeyUp = 0xC8,  // ��L�[
	KeyRight = 0xCD,  // �E�L�[
	KeyDown = 0xD0,  // ���L�[
	KeyInsert = 0xD2,  // �C���T�[�g�L�[
	KeyDelete = 0xD3,  // �f���[�g�L�[

	KeyMinus = 0x0C,  // �|�L�[
	KeyYen = 0x7D,  // ���L�[
	KeyPrevTrack = 0x90,  // �O�L�[
	KeyPeriod = 0x34,  // �D�L�[
	KeyLAlt = 0x35,  // ���`�k�s�L�[
	KeyRAlt = 0x38,  // �E�`�k�s�L�[
	KeySlash = 0xB8,  // �^�L�[
	KeyScrollLock = 0x46,  // ScrollLock�L�[
	KeySemicolon = 0x27,  // �G�L�[
	KeyColon = 0x92,  // �F�L�[
	KeyLBracket = 0x1A,  // �m�L�[
	KeyRBracket = 0x1B,  // �n�L�[
	KeyAt = 0x91,  // ���L�[
	KeyBackSlash = 0x2B,  // �_�L�[
	KeyComma = 0x33,  // �C�L�[
	KeyKanji = 0x94,  // �����L�[					
	KeyConvert = 0x79,  // �ϊ��L�[					
	KeyNoconvert = 0x7B,  // ���ϊ��L�[					
	KeyKana = 0x70,  // �J�i�L�[					
	KeyApps = 0xDD,  // �A�v���P�[�V�������j���[�L�[
	KeyCapsLock = 0x3A,  // CaspLock�L�[
	KeySysrq = 0xB7,  // PrintScreen�L�[				
	KeyPause = 0xC5,  // PauseBreak�L�[				
	KeyLwin = 0xDB,  // ��Win�L�[					
	KeyRwin = 0xDC,  // �EWin�L�[					

	KeyNumlock = 0x45,  // �e���L�[NumLock�L�[	
	KeyNumpad0 = 0x52,  // �e���L�[�O			
	KeyNumpad1 = 0x4F,  // �e���L�[�P			
	KeyNumpad2 = 0x50,  // �e���L�[�Q			
	KeyNumpad3 = 0x51,  // �e���L�[�R			
	KeyNumpad4 = 0x4B,  // �e���L�[�S			
	KeyNumpad5 = 0x4C,  // �e���L�[�T			
	KeyNumpad6 = 0x4D,  // �e���L�[�U			
	KeyNumpad7 = 0x47,  // �e���L�[�V			
	KeyNumpad8 = 0x48,  // �e���L�[�W			
	KeyNumpad9 = 0x49,  // �e���L�[�X			
	KeyMultiply = 0x37,  // �e���L�[���L�[		
	KeyAdd = 0x4E,  // �e���L�[�{�L�[		
	KeySubtract = 0x4A,  // �e���L�[�|�L�[		
	KeyDecimal = 0x53,  // �e���L�[�D�L�[		
	KeyDivide = 0xB5,  // �e���L�[�^�L�[		
	KeyNumpadenter = 0x9C,  // �e���L�[�̃G���^�[�L�[

	KeyF1 = 0x3B,  // �e�P�L�[
	KeyF2 = 0x3C,  // �e�Q�L�[
	KeyF3 = 0x3D,  // �e�R�L�[
	KeyF4 = 0x3E,  // �e�S�L�[
	KeyF5 = 0x3F,  // �e�T�L�[
	KeyF6 = 0x40,  // �e�U�L�[
	KeyF7 = 0x41,  // �e�V�L�[
	KeyF8 = 0x42,  // �e�W�L�[
	KeyF9 = 0x43,  // �e�X�L�[
	KeyF10 = 0x44,  // �e�P�O�L�[
	KeyF11 = 0x57,  // �e�P�P�L�[
	KeyF12 = 0x58,  // �e�P�Q�L�[

	KeyA = 0x1E,  // �`�L�[
	KeyB = 0x30,  // �a�L�[
	KeyC = 0x2E,  // �b�L�[
	KeyD = 0x20,  // �c�L�[
	KeyE = 0x12,  // �d�L�[
	KeyF = 0x21,  // �e�L�[
	KeyG = 0x22,  // �f�L�[
	KeyH = 0x23,  // �g�L�[
	KeyI = 0x17,  // �h�L�[
	KeyJ = 0x24,  // �i�L�[
	KeyK = 0x25,  // �j�L�[
	KeyL = 0x26,  // �k�L�[
	KeyM = 0x32,  // �l�L�[
	KeyN = 0x31,  // �m�L�[
	KeyO = 0x18,  // �n�L�[
	KeyP = 0x19,  // �o�L�[
	KeyQ = 0x10,  // �p�L�[
	KeyR = 0x13,  // �q�L�[
	KeyS = 0x1F,  // �r�L�[
	KeyT = 0x14,  // �s�L�[
	KeyU = 0x16,  // �t�L�[
	KeyV = 0x2F,  // �u�L�[
	KeyW = 0x11,  // �v�L�[
	KeyX = 0x2D,  // �w�L�[
	KeyY = 0x15,  // �x�L�[
	KeyZ = 0x2C,  // �y�L�[
	Key0 = 0x0B,  // �O�L�[
	Key1 = 0x02,  // �P�L�[
	Key2 = 0x03,  // �Q�L�[
	Key3 = 0x04,  // �R�L�[
	Key4 = 0x05,  // �S�L�[
	Key5 = 0x06,  // �T�L�[
	Key6 = 0x07,  // �U�L�[
	Key7 = 0x08,  // �V�L�[
	Key8 = 0x09,  // �W�L�[
	Key9 = 0x0A,  // �X�L�[

	//�}�E�X���͒�`
	MouseLeft = 0x1001,	// �}�E�X���{�^��
	MouseRight = 0x1002,	// �}�E�X�E�{�^��
	MouseMiddle = 0x1004,	// �}�E�X�����{�^��
	Mouse1 = 0x1001,	// �}�E�X�P�{�^��
	Mouse2 = 0x1002,	// �}�E�X�Q�{�^��
	Mouse3 = 0x1004,	// �}�E�X�R�{�^��
	Mouse4 = 0x1008,	// �}�E�X�S�{�^��
	Mouse5 = 0x1010,	// �}�E�X�T�{�^��
	Mouse6 = 0x1020,	// �}�E�X�U�{�^��
	Mouse7 = 0x1040,	// �}�E�X�V�{�^��
	Mouse8 = 0x1080,	// �}�E�X�W�{�^��

	//XInput�{�^�����͒�`
	PadDPadUp = 0x2000,		    // �f�W�^�������{�^����
	PadDPadDown,				// �f�W�^�������{�^����
	PadDPadLeft,				// �f�W�^�������{�^����
	PadDPadRight,			    // �f�W�^�������{�^���E
	PadStart,				    // START�{�^��
	PadBack,					// BACK�{�^��
	PadLeftThumbClick,		    // ���X�e�B�b�N��������
	PadRightThumbClick,		    // �E�X�e�B�b�N��������
	PadLeftShoulder,			// LB�{�^��
	PadRightShoulder,		    // RB�{�^��
	PadA,					    // A�{�^��
	PadB,					    // B�{�^��
	PadX,					    // X�{�^��
	PadY,					    // Y�{�^��
	PadLeftThumbTilt,		    // ���X�e�B�b�N�����ꂩ�̕�������
	PadLeftThumbTiltUp,		    // ���X�e�B�b�N���������
	PadLeftThumbTiltDown,	    // ���X�e�B�b�N����������
	PadLeftThumbTiltLeft,	    // ���X�e�B�b�N����������
	PadLeftThumbTiltRight,	    // ���X�e�B�b�N�E��������
	PadRightThumbTilt,		    // �E�X�e�B�b�N�����ꂩ�̕�������
	PadRightThumbTiltUp,		// �E�X�e�B�b�N���������
	PadRightThumbTiltDown,	    // �E�X�e�B�b�N����������
	PadRightThumbTiltLeft,	    // �E�X�e�B�b�N����������
	PadRightThumbTiltRight,	    // �E�X�e�B�b�N�E��������
	PadRightTrigger,            // �E�g���K�[
	PadLeftTrigger,             // ���g���K�[

	Pad1DPadUp = 0x3000,		// �p�b�h1�̃f�W�^�������{�^����
	Pad1DPadDown,				// �p�b�h1�̃f�W�^�������{�^����
	Pad1DPadLeft,				// �p�b�h1�̃f�W�^�������{�^����
	Pad1DPadRight,			    // �p�b�h1�̃f�W�^�������{�^���E
	Pad1Start,				    // �p�b�h1��START�{�^��
	Pad1Back,					// �p�b�h1��BACK�{�^��
	Pad1LeftThumbClick,		    // �p�b�h1�̍��X�e�B�b�N��������
	Pad1RightThumbClick,		// �p�b�h1�̉E�X�e�B�b�N��������
	Pad1LeftShoulder,			// �p�b�h1��LB�{�^��
	Pad1RightShoulder,		    // �p�b�h1��RB�{�^��
	Pad1A,					    // �p�b�h1��A�{�^��
	Pad1B,					    // �p�b�h1��B�{�^��
	Pad1X,					    // �p�b�h1��X�{�^��
	Pad1Y,					    // �p�b�h1��Y�{�^��
	Pad1LeftThumbTilt,		    // �p�b�h1�̍��X�e�B�b�N�����ꂩ�̕�������
	Pad1LeftThumbTiltUp,		// �p�b�h1�̍��X�e�B�b�N���������
	Pad1LeftThumbTiltDown,	    // �p�b�h1�̍��X�e�B�b�N����������
	Pad1LeftThumbTiltLeft,	    // �p�b�h1�̍��X�e�B�b�N����������
	Pad1LeftThumbTiltRight,	    // �p�b�h1�̍��X�e�B�b�N�E��������
	Pad1RightThumbTilt,		    // �p�b�h1�̉E�X�e�B�b�N�����ꂩ�̕�������
	Pad1RightThumbTiltUp,		// �p�b�h1�̉E�X�e�B�b�N���������
	Pad1RightThumbTiltDown,	    // �p�b�h1�̉E�X�e�B�b�N����������
	Pad1RightThumbTiltLeft,	    // �p�b�h1�̉E�X�e�B�b�N����������
	Pad1RightThumbTiltRight,	// �p�b�h1�̉E�X�e�B�b�N�E��������
	Pad1RightTrigger,           // �p�b�h1�E�g���K�[
	Pad1LeftTrigger,			// �p�b�h1���g���K�[

	Pad2DPadUp = 0x4000,		// �p�b�h2�̃f�W�^�������{�^����
	Pad2DPadDown,				// �p�b�h2�̃f�W�^�������{�^����
	Pad2DPadLeft,				// �p�b�h2�̃f�W�^�������{�^����
	Pad2DPadRight,			    // �p�b�h2�̃f�W�^�������{�^���E
	Pad2Start,				    // �p�b�h2��START�{�^��
	Pad2Back,					// �p�b�h2��BACK�{�^��
	Pad2LeftThumbClick,		    // �p�b�h2�̍��X�e�B�b�N��������
	Pad2RightThumbClick,		// �p�b�h2�̉E�X�e�B�b�N��������
	Pad2LeftShoulder,			// �p�b�h2��LB�{�^��
	Pad2RightShoulder,		    // �p�b�h2��RB�{�^��
	Pad2A,					    // �p�b�h2��A�{�^��
	Pad2B,					    // �p�b�h2��B�{�^��
	Pad2X,					    // �p�b�h2��X�{�^��
	Pad2Y,					    // �p�b�h2��Y�{�^��
	Pad2LeftThumbTilt,		    // �p�b�h2�̍��X�e�B�b�N�����ꂩ�̕�������
	Pad2LeftThumbTiltUp,		// �p�b�h2�̍��X�e�B�b�N���������
	Pad2LeftThumbTiltDown,	    // �p�b�h2�̍��X�e�B�b�N����������
	Pad2LeftThumbTiltLeft,	    // �p�b�h2�̍��X�e�B�b�N����������
	Pad2LeftThumbTiltRight,	    // �p�b�h2�̍��X�e�B�b�N�E��������
	Pad2RightThumbTilt,		    // �p�b�h2�̉E�X�e�B�b�N�����ꂩ�̕�������
	Pad2RightThumbTiltUp,		// �p�b�h2�̉E�X�e�B�b�N���������
	Pad2RightThumbTiltDown,	    // �p�b�h2�̉E�X�e�B�b�N����������
	Pad2RightThumbTiltLeft,	    // �p�b�h2�̉E�X�e�B�b�N����������
	Pad2RightThumbTiltRight,	// �p�b�h2�̉E�X�e�B�b�N�E��������
	Pad2RightTrigger,           // �p�b�h2�E�g���K�[
	Pad2LeftTrigger,			// �p�b�h2���g���K�[

	Pad3DPadUp = 0x5000,		// �p�b�h3�̃f�W�^�������{�^����
	Pad3DPadDown,				// �p�b�h3�̃f�W�^�������{�^����
	Pad3DPadLeft,				// �p�b�h3�̃f�W�^�������{�^����
	Pad3DPadRight,			    // �p�b�h3�̃f�W�^�������{�^���E
	Pad3Start,				    // �p�b�h3��START�{�^��
	Pad3Back,					// �p�b�h3��BACK�{�^��
	Pad3LeftThumbClick,		    // �p�b�h3�̍��X�e�B�b�N��������
	Pad3RightThumbClick,		// �p�b�h3�̉E�X�e�B�b�N��������
	Pad3LeftShoulder,			// �p�b�h3��LB�{�^��
	Pad3RightShoulder,		    // �p�b�h3��RB�{�^��
	Pad3A,					    // �p�b�h3��A�{�^��
	Pad3B,					    // �p�b�h3��B�{�^��
	Pad3X,					    // �p�b�h3��X�{�^��
	Pad3Y,					    // �p�b�h3��Y�{�^��
	Pad3LeftThumbTilt,		    // �p�b�h3�̍��X�e�B�b�N�����ꂩ�̕�������
	Pad3LeftThumbTiltUp,		// �p�b�h3�̍��X�e�B�b�N���������
	Pad3LeftThumbTiltDown,	    // �p�b�h3�̍��X�e�B�b�N����������
	Pad3LeftThumbTiltLeft,	    // �p�b�h3�̍��X�e�B�b�N����������
	Pad3LeftThumbTiltRight,	    // �p�b�h3�̍��X�e�B�b�N�E��������
	Pad3RightThumbTilt,		    // �p�b�h3�̉E�X�e�B�b�N�����ꂩ�̕�������
	Pad3RightThumbTiltUp,		// �p�b�h3�̉E�X�e�B�b�N���������
	Pad3RightThumbTiltDown,	    // �p�b�h3�̉E�X�e�B�b�N����������
	Pad3RightThumbTiltLeft,	    // �p�b�h3�̉E�X�e�B�b�N����������
	Pad3RightThumbTiltRight,	// �p�b�h3�̉E�X�e�B�b�N�E��������
	Pad3RightTrigger,           // �p�b�h3�E�g���K�[
	Pad3LeftTrigger,			// �p�b�h3���g���K�[

	Pad4DPadUp = 0x6000,		// �p�b�h4�̃f�W�^�������{�^����
	Pad4DPadDown,				// �p�b�h4�̃f�W�^�������{�^����
	Pad4DPadLeft,				// �p�b�h4�̃f�W�^�������{�^����
	Pad4DPadRight,			    // �p�b�h4�̃f�W�^�������{�^���E
	Pad4Start,				    // �p�b�h4��START�{�^��
	Pad4Back,					// �p�b�h4��BACK�{�^��
	Pad4LeftThumbClick,		    // �p�b�h4�̍��X�e�B�b�N��������
	Pad4RightThumbClick,		// �p�b�h4�̉E�X�e�B�b�N��������
	Pad4LeftShoulder,			// �p�b�h4��LB�{�^��
	Pad4RightShoulder,		    // �p�b�h4��RB�{�^��
	Pad4A,					    // �p�b�h4��A�{�^��
	Pad4B,					    // �p�b�h4��B�{�^��
	Pad4X,					    // �p�b�h4��X�{�^��
	Pad4Y,					    // �p�b�h4��Y�{�^��
	Pad4LeftThumbTilt,		    // �p�b�h4�̍��X�e�B�b�N�����ꂩ�̕�������
	Pad4LeftThumbTiltUp,		// �p�b�h4�̍��X�e�B�b�N���������
	Pad4LeftThumbTiltDown,	    // �p�b�h4�̍��X�e�B�b�N����������
	Pad4LeftThumbTiltLeft,	    // �p�b�h4�̍��X�e�B�b�N����������
	Pad4LeftThumbTiltRight,	    // �p�b�h4�̍��X�e�B�b�N�E��������
	Pad4RightThumbTilt,		    // �p�b�h4�̉E�X�e�B�b�N�����ꂩ�̕�������
	Pad4RightThumbTiltUp,		// �p�b�h4�̉E�X�e�B�b�N���������
	Pad4RightThumbTiltDown,	    // �p�b�h4�̉E�X�e�B�b�N����������
	Pad4RightThumbTiltLeft,	    // �p�b�h4�̉E�X�e�B�b�N����������
	Pad4RightThumbTiltRight,	// �p�b�h4�̉E�X�e�B�b�N�E��������
	Pad4RightTrigger,           // �p�b�h4�E�g���K�[
	Pad4LeftTrigger,			// �p�b�h4���g���K�[
};