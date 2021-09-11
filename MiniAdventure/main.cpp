#include "DxLib.h"

const char TITLE[] = "Mini Adventure";

const int WIN_WIDTH = 320; //�E�B���h�E����
const int WIN_HEIGHT = 256;//�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	//�v���C���[�P
	int gh2[4];

	//�����ǂݍ��݁@�v2���@��2�@�c1�@�傫��48x48
	LoadDivGraph("player.png", 3, 3, 1, 48, 48, gh2);

	int playerX;
	int playerY;
	int playerR;

	int animation;

	int tutorial = 200;

	//�{�^������
	int button1;
	int button2;
	int button3;
	int button4;
	int button5;
	int button6;
	int button7;
	int button8;
	int button9;
	int button10;
	int button11;

	//�n���}�[����
	int hammer;

	//�R�C��
	int coin1;
	int coin2;
	int coin3;

	//��
	int rock;

	//��ʃX�N���[���p
	int sx;
	int sy;

	//�u���b�N�@�����ǂݍ��݁@�v15���@��10�@�c2�@�傫��64x64
	int gh4[30];
	LoadDivGraph("Blocks.png", 16, 10, 2, 64, 64, gh4);

	//HUD
	int gh5 = LoadGraph("HUD.png");

	int gh6 = LoadGraph("HUD 2.png");

	//�R�C���@�����ǂݍ��݁@�v4���@��4�@�c1�@�傫��64x64
	int gh7[5];
	LoadDivGraph("coin.png", 4, 4, 1, 64, 64, gh7);

	//�^�C�g�����
	int gh8 = LoadGraph("Title.png");

	//HUD�p�R�C���摜
	int gh9 = LoadGraph("HUD coin.png");

	//���U���g��ʗp�摜
	int gh10 = LoadGraph("Result.png");
	int gh11 = LoadGraph("result coin.png");

	int gh12 = LoadGraph("Rank C.png");
	int gh13 = LoadGraph("Rank C 2.png");
	int gh14 = LoadGraph("Rank B.png");
	int gh15 = LoadGraph("Rank B 2.png");
	int gh16 = LoadGraph("Rank A.png");
	int gh17 = LoadGraph("Rank A 2.png");
	int gh18 = LoadGraph("Rank S.png");
	int gh19 = LoadGraph("Rank Idiot.png");
	int gh20 = LoadGraph("Idiot result.png");
	int gh23 = LoadGraph("Rank Idiot 2.png");
	int gh24 = LoadGraph("Idiot result 2.png");

	int gh25 = LoadGraph("HUD 3.png");
	int gh26 = LoadGraph("HUD 4.png");

	int gh27 = LoadGraph("tutorial pad.png");

	int gh21[6];
	LoadDivGraph("compass.png", 5, 5, 1, 32, 32, gh21);

	int gh22 = LoadGraph("Credit.png");

	int BGM1 = LoadSoundMem("bgm_maoudamashii_8bit13.mp3");
	ChangeVolumeSoundMem(255 * 38 / 100, BGM1);

	int BGM2 = LoadSoundMem("bgm_maoudamashii_8bit14.mp3");
	ChangeVolumeSoundMem(255 * 38 / 100, BGM2);

	int BGM3 = LoadSoundMem("You are an idiot.mp3");
	ChangeVolumeSoundMem(255 * 38 / 100, BGM3);

	int flag1 = 1;
	int flag2 = 1;
	int flag3 = 1;
	int flag4 = 1;

	//�X�e�[�W�}�b�v�`�b�v
	int mapdata[30][20] =
	{
		{ 0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
		{ 0, 4, 4, 4, 0,  4, 4, 0, 4, 2,  4, 0, 4, 2, 4,  0, 4, 4, 4, 0},
		{ 0, 4, 4, 4, 0,  4, 0, 0, 4, 0,  4, 2, 4, 3, 4,  1, 4, 0, 4, 0},
		{ 0, 4, 4, 4, 0,  4, 0, 5, 0, 0,  0, 0, 0, 0, 0,  0, 0, 4, 4, 0},
		{ 0, 0, 4, 0, 0,  4, 0, 4, 4, 0,  0, 4, 1, 4, 4,  4, 4, 4, 4, 0},

		{ 0, 4, 4, 4, 4,  4, 0, 0, 4, 0,  4, 4, 0, 4, 4,  4, 4, 4, 4, 0},
		{ 0, 4, 0, 0, 0,  4, 4, 0, 4, 0,  4, 0, 4, 4, 0,  0, 0, 0, 4, 0},
		{ 0, 4, 4, 0, 0,  0, 4, 0, 4, 0,  4, 0, 4, 0, 4,  5, 0, 4, 4, 0},
		{ 0, 0, 4, 0, 4,  1, 4, 4, 4, 0,  8, 0, 4, 0, 4,  0, 8, 3, 4, 0},
		{ 0, 4, 4, 0, 5,  0, 0, 0, 0, 0,  0, 0, 4, 0, 4,  4, 0, 4, 4, 0},

		{ 0, 4, 0, 0, 0,  0, 4, 1, 4, 1,  4, 4, 4, 0, 4,  4, 0, 4, 0, 0},
		{ 0, 4, 4, 0, 4,  4, 4, 0, 4, 0,  0, 0, 4, 0, 0,  4, 0, 4, 5, 0},
		{ 0, 0, 4, 4, 4,  0, 4, 0, 4, 0,  5, 0, 4, 0, 0,  4, 0, 4, 0, 0},
		{ 0, 4, 4, 0, 0,  0, 4, 0, 4, 0,  4, 0, 4, 4, 4,  4, 4, 4, 4, 0},
		{ 0, 4, 4, 0, 8,  0, 4, 0, 4, 0,  4, 0, 0, 0, 0,  0, 0, 0, 4, 0},

		{ 0, 0, 5, 0, 4,  4, 4, 0, 8, 0,  4, 4, 4, 4, 4,  4, 4, 4, 4, 0},
		{ 0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  4, 0, 0, 0, 0},
		{ 0, 4, 0, 4, 4,  4, 4, 4, 4, 4,  4, 4, 4, 4, 4,  4, 4, 4, 4, 0},
		{ 0, 4, 4, 0, 4,  0, 0, 0, 0, 0,  4, 0, 0, 0, 4,  0, 0, 0, 4, 0},
		{ 0, 0, 4, 4, 4,  4, 4, 5, 0, 5,  4, 4, 4, 4, 4,  4, 4, 4, 4, 0},

		{ 0, 5, 2, 4, 4,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 4, 0, 0, 0},
		{ 0, 0, 4, 4, 4,  4, 4, 5, 0, 5,  4, 4, 4, 0, 4,  4, 4, 4, 4, 0},
		{ 0, 4, 4, 0, 1,  0, 0, 0, 0, 0,  0, 0, 4, 0, 4,  4, 0, 0, 4, 0},
		{ 0, 4, 0, 4, 4,  4, 0, 4, 0, 8,  0, 0, 4, 0, 4,  4, 4, 0, 4, 0},
		{ 0, 0, 4, 4, 0,  4, 4, 0, 0, 4,  4, 0, 4, 0, 4,  0, 0, 4, 4, 0},

		{ 0, 4, 4, 0, 4,  0, 4, 4, 0, 0,  4, 0, 2, 0, 4,  4, 4, 4, 0, 0},
		{ 0, 4, 4, 0, 4,  0, 4, 4, 0, 4,  4, 0, 4, 3, 4,  4, 4, 0, 8, 0},
		{ 0, 4, 0, 0, 1,  0, 0, 4, 0, 4,  0, 0, 4, 0, 4,  4, 0, 0, 4, 0},
		{ 0, 4, 4, 4, 4,  4, 4, 4, 0, 4,  4, 4, 2, 3, 2,  4, 4, 4, 4, 0},
		{ 0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},

	};


	//�Q�[���V�[������
	int scene = 0;

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����

		switch (scene)
		{
			//�^�C�g����ʏ���
		case 0:

			if (flag4 == 1)
			{
				StopSoundMem(BGM2);
				StopSoundMem(BGM3);

				if (CheckSoundMem(BGM1) == 0)
				{
					PlaySoundMem(BGM1, DX_PLAYTYPE_BACK);
				}
			}

			DrawGraph(0, 0, gh8, TRUE);

			if (keys[KEY_INPUT_Z] == 1)
			{
				scene = 1;

				playerX = 160;
				playerY = 128;
				playerR = 24;

				animation = 0;

				//�{�^������
				button1 = 0;
				button2 = 0;
				button3 = 0;
				button4 = 0;
				button5 = 0;
				button6 = 0;
				button7 = 0;
				button8 = 0;
				button9 = 0;
				button10 = 0;
				button11 = 0;

				//�n���}�[����
				hammer = 0;

				//�R�C��
				coin1 = 0;
				coin2 = 0;
				coin3 = 0;

				//��
				rock = 0;

				//��ʃX�N���[���p
				sx = 0;
				sy = 0;

				//��
				mapdata[8][5] = 1;
				mapdata[10][7] = 1;
				mapdata[10][9] = 1;
				mapdata[4][12] = 1;
				mapdata[2][15] = 1;
				mapdata[22][4] = 1;
				mapdata[27][4] = 1;

				//��
				mapdata[1][9] = 2;
				mapdata[2][11] = 2;
				mapdata[1][13] = 2;
				mapdata[20][2] = 2;
				mapdata[25][12] = 2;
				mapdata[28][12] = 2;
				mapdata[28][14] = 2;

				//�ړ���
				mapdata[2][13] = 3;
				mapdata[8][17] = 3;
				mapdata[26][13] = 3;
				mapdata[28][13] = 3;

				//�Ő�
				mapdata[1][1] = 4;

				//�{�^��
				mapdata[3][7] = 5;
				mapdata[9][4] = 5;
				mapdata[15][2] = 5;
				mapdata[12][10] = 5;
				mapdata[7][15] = 5;
				mapdata[11][18] = 5;
				mapdata[20][1] = 5;
				mapdata[19][7] = 5;
				mapdata[21][7] = 5;
				mapdata[19][9] = 5;
				mapdata[21][9] = 5;

				//�n���}�[
				mapdata[14][4] = 8;
				mapdata[15][8] = 8;
				mapdata[8][10] = 8;
				mapdata[8][16] = 8;
				mapdata[26][18] = 8;
				mapdata[23][9] = 8;
			}

			if (flag1 == 1)
			{
				if ((CheckSoundMem(BGM1) == 0) && (CheckSoundMem(BGM2) == 0))
				{
					PlaySoundMem(BGM1, DX_PLAYTYPE_BACK);
				}
			}
			break;




		case 1:

			if (flag2 == 1)
			{
				StopSoundMem(BGM1);

				if (CheckSoundMem(BGM2) == 0)
				{
					PlaySoundMem(BGM2, DX_PLAYTYPE_BACK);
				}
			}

			//�v���C���[����
			if (keys[KEY_INPUT_UP] == 1)
			{
				if ((mapdata[(playerY - playerR - 3) / 64][(playerX - playerR) / 64] > 3) &&
					(mapdata[(playerY - playerR - 3) / 64][(playerX + playerR) / 64] > 3))
				{
					playerY -= 3;
				}

				if (playerY - sy < 128)
				{
					sy -= 3;
				}

				if (sy < 0)
				{
					sy = 0;
				}
			}

			if (keys[KEY_INPUT_LEFT] == 1)
			{
				if ((mapdata[(playerY - playerR) / 64][(playerX - playerR - 3) / 64] > 3) &&
					(mapdata[(playerY + playerR) / 64][(playerX - playerR - 3) / 64] > 3))
				{
					playerX -= 3;
				}

				if (playerX - sx < 160)
				{
					sx -= 3;
				}

				if (sx < 0)
				{
					sx = 0;
				}
			}

			if (keys[KEY_INPUT_DOWN] == 1)
			{
				if ((mapdata[(playerY + playerR + 3) / 64][(playerX - playerR) / 64] > 3) &&
					(mapdata[(playerY + playerR + 3) / 64][(playerX + playerR) / 64] > 3))
				{
					playerY += 3;
				}

				if (playerY - sy > 128)
				{
					sy += 3;
				}
			}

			if (keys[KEY_INPUT_RIGHT] == 1)
			{
				if ((mapdata[(playerY - playerR) / 64][(playerX + playerR + 3) / 64] > 3) &&
					(mapdata[(playerY + playerR) / 64][(playerX + playerR + 3) / 64] > 3))
				{
					playerX += 3;
				}

				if (playerX - sx > 160)
				{
					sx += 3;
				}

				if (sx > 960)
				{
					sx = 960;
				}
			}

			/////////////�{�^������//////////////
			//�{�^��1_.
			if ((playerY / 64 == 3) && (playerX / 64 == 7))
			{
				button1 = 1;
			}

			//�{�^��2
			if ((playerY / 64 == 15) && (playerX / 64 == 2))
			{
				button2 = 1;
			}

			//�{�^��3
			if ((playerY / 64 == 9) && (playerX / 64 == 4))
			{
				button3 = 1;
			}

			//�{�^��4
			if ((playerY / 64 == 12) && (playerX / 64 == 10))
			{
				button4 = 1;
			}

			//�{�^��5
			if ((playerY / 64 == 11) && (playerX / 64 == 18))
			{
				button5 = 1;
			}

			//�{�^��6
			if ((playerY / 64 == 7) && (playerX / 64 == 15))
			{
				button6 = 1;
			}

			//�{�^��7
			if ((playerY / 64 == 19) && (playerX / 64 == 7))
			{
				button7 = 1;
			}

			//�{�^��8
			if ((playerY / 64 == 19) && (playerX / 64 == 9))
			{
				button8 = 1;
			}

			//�{�^��9
			if ((playerY / 64 == 21) && (playerX / 64 == 9))
			{
				button9 = 1;
			}

			//�{�^��10
			if ((playerY / 64 == 21) && (playerX / 64 == 7))
			{
				button10 = 1;
			}

			//�{�^��11
			if ((playerY / 64 == 20) && (playerX / 64 == 1))
			{
				button11 = 1;
			}

			///////�n���}�[����///////////

			if ((playerY / 64 == 14) && (playerX / 64 == 4) &&
				(mapdata[14][4] == 8) && (hammer < 3))
			{
				hammer += 1;
			}

			if ((playerY / 64 == 15) && (playerX / 64 == 8) &&
				(mapdata[15][8] == 8) && (hammer < 3))
			{
				hammer += 1;
			}

			if ((playerY / 64 == 8) && (playerX / 64 == 10) &&
				(mapdata[8][10] == 8) && (hammer < 3))
			{
				hammer += 1;
			}

			if ((playerY / 64 == 8) && (playerX / 64 == 16) &&
				(mapdata[8][16] == 8) && (hammer < 3))
			{
				hammer += 1;
			}

			if ((playerY / 64 == 26) && (playerX / 64 == 18) &&
				(mapdata[26][18] == 8) && (hammer < 3))
			{
				hammer += 1;
			}

			if ((playerY / 64 == 23) && (playerX / 64 == 9) &&
				(mapdata[23][9] == 8) && (hammer < 3))
			{
				hammer += 1;
			}


			///////////�R�C������//////////////
			//�R�C��1�擾
			if ((playerY / 64 == 2) && (playerX / 64 == 8))
			{
				coin1 = 1;
			}

			//�R�C��2�擾
			if ((playerY / 64 == 23) && (playerX / 64 == 16))
			{
				coin2 = 1;
			}

			//�R�C��3�擾
			if ((playerY / 64 == 25) && (playerX / 64 == 4))
			{
				coin3 = 1;
			}


			//�`�揈��
			//�X�e�[�W�`��
			for (int x = 0; x < 20; x++)
			{
				for (int y = 0; y < 30; y++)
				{
					DrawGraph((x * 64) - sx, (y * 64) - sy, gh4[mapdata[y][x]], FALSE);

					//�n���}�[�l���̏���
					//�n���}�[1
					if ((playerY / 64 == 14) && (playerX / 64 == 4) && (hammer <= 3))
					{
						mapdata[14][4] = 4;
					}

					//�n���}�[2
					if ((playerY / 64 == 15) && (playerX / 64 == 8) && (hammer <= 3))
					{
						mapdata[15][8] = 4;
					}

					//�n���}�[3
					if ((playerY / 64 == 8) && (playerX / 64 == 10) && (hammer <= 3))
					{
						mapdata[8][10] = 4;
					}

					//�n���}�[4
					if ((playerY / 64 == 8) && (playerX / 64 == 16) && (hammer <= 3))
					{
						mapdata[8][16] = 4;
					}

					//�n���}�[5
					if ((playerY / 64 == 26) && (playerX / 64 == 18) && (hammer <= 3))
					{
						mapdata[26][18] = 4;
					}

					//�n���}�[6
					if ((playerY / 64 == 23) && (playerX / 64 == 9) && (hammer <= 3))
					{
						mapdata[23][9] = 4;
					}


					///////�{�^���`�揈��///////
					//�{�^��1���������ۂ̕`�揈��
					if (button1 == 1)
					{
						mapdata[3][7] = 6;
						mapdata[10][9] = 7;
					}

					//�{�^��2���������ۂ̕`�揈��
					if (button2 == 1)
					{
						mapdata[15][2] = 6;
						mapdata[8][5] = 7;
					}

					//�{�^��3���������ۂ̕`�揈��
					if (button3 == 1)
					{
						mapdata[9][4] = 6;
						mapdata[10][7] = 7;
					}

					//�{�^��4���������ۂ̕`�揈��
					if (button4 == 1)
					{
						mapdata[12][10] = 6;
						mapdata[2][15] = 7;
					}

					//�{�^��5���������ۂ̕`�揈��
					if (button5 == 1)
					{
						mapdata[11][18] = 6;
						mapdata[4][12] = 7;
					}

					//�{�^��6���������ۂ̕`�揈��
					if (button6 == 1)
					{
						mapdata[7][15] = 6;
						mapdata[2][13] = 4;
					}

					//�{�^��7���������ۂ̕`�揈��
					if (button7 == 1)
					{
						mapdata[19][7] = 6;
						mapdata[28][13] = 15;
					}

					//�{�^��8���������ۂ̕`�揈��
					if (button8 == 1)
					{
						mapdata[19][9] = 6;
						mapdata[8][17] = 4;
					}

					//�{�^��9���������ۂ̕`�揈��
					if (button9 == 1)
					{
						mapdata[21][9] = 6;
						mapdata[22][4] = 7;
					}

					//�{�^��10���������ۂ̕`�揈��
					if (button10 == 1)
					{
						mapdata[21][7] = 6;
						mapdata[26][13] = 4;
					}

					//�{�^��11���������ۂ̕`�揈��
					if (button11 == 1)
					{
						mapdata[20][1] = 6;
						mapdata[27][4] = 7;
					}

					//�R�C��1�̕`��ƃA�j���[�V��������
					if (coin1 == 0)
					{
						if (animation < 10)
						{
							mapdata[2][8] = 10;
						}

						if ((animation >= 10) && (animation < 20))
						{
							mapdata[2][8] = 11;
						}

						if ((animation >= 20) && (animation < 30))
						{
							mapdata[2][8] = 12;
						}

						if ((animation >= 30) && (animation <= 40))
						{
							mapdata[2][8] = 13;
						}

						if ((animation >= 40) && (animation <= 50))
						{
							mapdata[2][8] = 10;
						}

						if ((animation >= 50) && (animation <= 60))
						{
							mapdata[2][8] = 11;
						}

						if ((animation >= 60) && (animation <= 70))
						{
							mapdata[2][8] = 12;
						}

						if ((animation >= 70) && (animation <= 80))
						{
							mapdata[2][8] = 13;
						}

						if (animation > 79)
						{
							animation = 0;
						}
					}

					if (coin1 == 1)
					{
						mapdata[2][8] = 4;
					}


					//�R�C��2�̕`�ʂƃA�j���[�V����
					if (coin2 == 0)
					{
						if (animation < 10)
						{
							mapdata[23][16] = 10;
						}

						if ((animation >= 10) && (animation < 20))
						{
							mapdata[23][16] = 11;
						}

						if ((animation >= 20) && (animation < 30))
						{
							mapdata[23][16] = 12;
						}

						if ((animation >= 30) && (animation <= 40))
						{
							mapdata[23][16] = 13;
						}

						if ((animation >= 40) && (animation <= 50))
						{
							mapdata[23][16] = 10;
						}

						if ((animation >= 50) && (animation <= 60))
						{
							mapdata[23][16] = 11;
						}

						if ((animation >= 60) && (animation <= 70))
						{
							mapdata[23][16] = 12;
						}

						if ((animation >= 70) && (animation <= 80))
						{
							mapdata[23][16] = 13;
						}

						if (animation > 79)
						{
							animation = 0;
						}
					}

					if (coin2 == 1)
					{
						mapdata[23][16] = 4;
					}


					//�R�C��3�̕`�ʂƃA�j���[�V����
					if (coin3 == 0)
					{
						if (animation < 10)
						{
							mapdata[25][4] = 10;
						}

						if ((animation >= 10) && (animation < 20))
						{
							mapdata[25][4] = 11;
						}

						if ((animation >= 20) && (animation < 30))
						{
							mapdata[25][4] = 12;
						}

						if ((animation >= 30) && (animation <= 40))
						{
							mapdata[25][4] = 13;
						}

						if ((animation >= 40) && (animation <= 50))
						{
							mapdata[25][4] = 10;
						}

						if ((animation >= 50) && (animation <= 60))
						{
							mapdata[25][4] = 11;
						}

						if ((animation >= 60) && (animation <= 70))
						{
							mapdata[25][4] = 12;
						}

						if ((animation >= 70) && (animation <= 80))
						{
							mapdata[25][4] = 13;
						}

						if (animation > 79)
						{
							animation = 0;
						}
					}

					if (coin3 == 1)
					{
						mapdata[25][4] = 4;
					}
				}
			}

			///////////�n���}�[����///////////
			if ((playerY / 64 == 14) && (playerX / 64 == 4) &&
				(mapdata[14][4] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			if ((playerY / 64 == 15) && (playerX / 64 == 8) &&
				(mapdata[15][8] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			if ((playerY / 64 == 8) && (playerX / 64 == 10) &&
				(mapdata[8][10] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			if ((playerY / 64 == 8) && (playerX / 64 == 16) &&
				(mapdata[8][16] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			if ((playerY / 64 == 26) && (playerX / 64 == 18) &&
				(mapdata[26][18] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			if ((playerY / 64 == 23) && (playerX / 64 == 9) &&
				(mapdata[23][9] == 4) && (hammer > 3))
			{
				hammer += 0;
			}

			//�n���}�[�g�p�̏���
			if (hammer > 0)
			{
				if (keys[KEY_INPUT_SPACE] == 1)
				{
					//1
					if ((playerY / 64 == 1) && (playerX / 64 == 14))
					{
						if (mapdata[1][13] == 2)
						{
							mapdata[1][13] = 9;
							hammer -= 1;
						}
					}

					//2
					if ((playerY / 64 == 2) && (playerX / 64 == 12))
					{
						if (mapdata[2][11] == 2)
						{
							mapdata[2][11] = 9;
							hammer -= 1;
						}
					}

					//3
					if ((playerY / 64 == 1) && (playerX / 64 == 10))
					{
						if (mapdata[1][9] == 2)
						{
							mapdata[1][9] = 9;
							hammer -= 1;
						}
					}

					//4
					if ((playerY / 64 == 28) && (playerX / 64 == 15))
					{
						if (mapdata[28][14] == 2)
						{
							mapdata[28][14] = 9;
							hammer -= 1;
						}
					}

					//5
					if ((playerY / 64 == 27) && (playerX / 64 == 14))
					{
						if (mapdata[28][14] == 2)
						{
							mapdata[28][14] = 9;
							hammer -= 1;
						}
					}

					//6
					if ((playerY / 64 == 27) && (playerX / 64 == 12))
					{
						if (mapdata[28][12] == 2)
						{
							mapdata[28][12] = 9;
							hammer -= 1;
						}
					}

					//7
					if ((playerY / 64 == 26) && (playerX / 64 == 12))
					{
						if (mapdata[25][12] == 2)
						{
							mapdata[25][12] = 9;
							hammer -= 1;
						}
					}

					//8
					if ((playerY / 64 == 28) && (playerX / 64 == 11))
					{
						if (mapdata[28][12] == 2)
						{
							mapdata[28][12] = 9;
							hammer -= 1;
						}
					}

					//9
					if ((playerY / 64 == 19) && (playerX / 64 == 2))
					{
						if (mapdata[20][2] == 2)
						{
							mapdata[20][2] = 9;
							hammer -= 1;
						}
					}

					//10
					if ((playerY / 64 == 20) && (playerX / 64 == 3))
					{
						if (mapdata[20][2] == 2)
						{
							mapdata[20][2] = 9;
							hammer -= 1;
						}
					}

					//11
					if ((playerY / 64 == 21) && (playerX / 64 == 2))
					{
						if (mapdata[20][2] == 2)
						{
							mapdata[20][2] = 9;
							hammer -= 1;
						}
					}
				}
			}

			if ((playerY / 64 == 28) && (playerX / 64 == 13))
			{
				scene = 2;
			}

			//�C�[�X�^�[�G�b�O(�����Y)
			if ((mapdata[3][7] == 6) && (mapdata[15][2] == 6) && (mapdata[9][4] == 6) &&
				(mapdata[12][10] == 6) && (mapdata[11][18] == 6) && (mapdata[7][15] == 6) &&
				(mapdata[19][7] == 6) && (mapdata[19][9] == 6) && (mapdata[21][9] == 6) &&
				(mapdata[21][7] == 6) && (mapdata[20][1] == 6))
			{
				mapdata[1][1] = 14;
			}


			////////////�A�j���[�V��������//////////////
			animation += 1;

			if (animation < 20)
			{
				DrawGraph(playerX - playerR - sx, playerY - playerR - sy, gh2[0], TRUE);
			}

			if ((animation >= 20) && (animation < 40))
			{
				DrawGraph(playerX - playerR - sx, playerY - playerR - sy, gh2[1], TRUE);
			}

			if ((animation >= 40) && (animation < 60))
			{
				DrawGraph(playerX - playerR - sx, playerY - playerR - sy, gh2[2], TRUE);
			}

			if ((animation >= 60) && (animation <= 80))
			{
				DrawGraph(playerX - playerR - sx, playerY - playerR - sy, gh2[1], TRUE);
			}

			if (animation > 79)
			{
				animation = 0;
			}

			//HUD
			DrawGraph(0, 192, gh5, TRUE);

			//�S�[���ւ̓������
			if ((playerY / 64 == 28) && (playerX / 64 < 13))
			{
				DrawGraph(144, 2, gh21[0], TRUE);
			}

			if ((playerX / 64 < 13) && (playerY / 64 < 28))
			{
				DrawGraph(144, 2, gh21[1], TRUE);
			}

			if ((playerX / 64 == 13) && (playerY / 64 < 28))
			{
				DrawGraph(144, 2, gh21[2], TRUE);
			}

			if ((playerX / 64 > 13) && (playerY / 64 < 28))
			{
				DrawGraph(144, 2, gh21[3], TRUE);
			}

			if ((playerX / 64 > 13) && (playerY / 64 == 28))
			{
				DrawGraph(144, 2, gh21[4], TRUE);
			}

			//HUD�p�n���}�[
			if (hammer == 1)
			{
				DrawGraph(0, 192, gh6, TRUE);
			}

			if (hammer == 2)
			{
				DrawGraph(0, 192, gh25, TRUE);
			}

			if (hammer == 3)
			{
				DrawGraph(0, 192, gh26, TRUE);
			}

			//HUD�p�R�C��1
			if (coin1 == 1)
			{
				DrawGraph(208, 208, gh9, TRUE);
			}

			if (coin2 == 1)
			{
				DrawGraph(240, 208, gh9, TRUE);
			}

			if (coin3 == 1)
			{
				DrawGraph(272, 208, gh9, TRUE);
			}

			//�`���[�g���A���p�p�b�h�\��
			tutorial -= 1;

			if (tutorial > 0)
			{
				DrawGraph(playerX - 32 - sx, playerY - 80 - sy, gh27, TRUE);
			}

			/*DrawBox(0, 0, 150, 80, GetColor(0, 0, 0), TRUE);

			DrawFormatString(0, 0, GetColor(255, 255, 255), "PlayerX = %d", playerX - sx);
			DrawFormatString(0, 20, GetColor(255, 255, 255), "PlayerY = %d", playerY - sy);
			DrawFormatString(0, 40, GetColor(255, 255, 255), "ScrollX = %d", sx);
			DrawFormatString(0, 60, GetColor(255, 255, 255), "ScrollY = %d", sy);*/

			break;


			//�N���A���
		case 2:

			animation += 1;

			if (animation > 40)
			{
				animation = 0;
			}

			DrawGraph(0, 0, gh10, TRUE);

			if (coin1 == 1)
			{
				DrawGraph(48, 48, gh11, TRUE);
				DrawGraph(32, 128, gh12, TRUE);
			}

			if (coin2 == 1)
			{
				DrawGraph(128, 48, gh11, TRUE);
				DrawGraph(32, 128, gh13, TRUE);
			}

			if (coin3 == 1)
			{
				DrawGraph(208, 48, gh11, TRUE);
				DrawGraph(32, 128, gh14, TRUE);
			}

			if ((coin1 == 1) && (coin2 == 1))
			{
				DrawGraph(48, 48, gh11, TRUE);
				DrawGraph(128, 48, gh11, TRUE);
				DrawGraph(32, 128, gh15, TRUE);
			}

			if ((coin1 == 1) && (coin3 == 1))
			{
				DrawGraph(48, 48, gh11, TRUE);
				DrawGraph(208, 48, gh11, TRUE);
				DrawGraph(32, 128, gh16, TRUE);
			}

			if ((coin2 == 1) && (coin3 == 1))
			{
				DrawGraph(128, 48, gh11, TRUE);
				DrawGraph(208, 48, gh11, TRUE);
				DrawGraph(32, 128, gh17, TRUE);
			}

			if ((coin1 == 1) && (coin2 == 1) && (coin3 == 1))
			{
				DrawGraph(48, 48, gh11, TRUE);
				DrawGraph(128, 48, gh11, TRUE);
				DrawGraph(208, 48, gh11, TRUE);
				DrawGraph(32, 128, gh18, TRUE);
			}

			if ((coin1 == 0) && (coin2 == 0) && (coin3 == 0))
			{
				if (flag3 == 1)
				{
					StopSoundMem(BGM2);

					if (CheckSoundMem(BGM3) == 0)
					{
						PlaySoundMem(BGM3, DX_PLAYTYPE_BACK);
					}
				}

				if (animation < 20)
				{
					DrawGraph(0, 0, gh20, TRUE);
					DrawGraph(32, 128, gh19, TRUE);
				}
				if (animation >= 20)
				{
					DrawGraph(0, 0, gh24, TRUE);
					DrawGraph(32, 128, gh23, TRUE);
				}

			}

			if (keys[KEY_INPUT_C] == 1)
			{
				scene = 3;
			}

			if (keys[KEY_INPUT_T] == 1)
			{
				scene = 0;
			}

			break;

			//�N���W�b�g
		case 3:

			DrawGraph(0, 0, gh22, TRUE);

			if (keys[KEY_INPUT_TAB] == 1)
			{
				scene = 2;
			}

			break;
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}