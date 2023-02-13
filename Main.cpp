#include"Loader.h"
#include<raylib.h>
#include<stdint.h>
#include<string>

typedef struct
{
	Color COL;
	uint16_t ID;
}sBlock;

sBlock Level[7][7] =
{
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},2}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},1},	{{255,0,0,128},0},	{{255,0,0,128},1},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},}



};

class Player
{
public:
	int x = 0;
	int y = 32;

	bool Fourcollision(int x, int y)
	{
		if (Level[(size_t)((y) / 32)][(size_t)(x / 32)].ID == 1)
		{
			if (CheckCollisionRecs(Rectangle{ (float)x , (float)(y), 32,32 }, Rectangle{ (float)(x / 32) * 32,(float)((y) / 32) * 32,32,32 }))
			{
				return true;
			}
		}
		if (Level[(size_t)((y) / 32 + 1)][(size_t)(x / 32)].ID == 1)
		{
			if (CheckCollisionRecs(Rectangle{ (float)x , (float)(y), 32,32 }, Rectangle{ (float)(x / 32) * 32,(float)((y) / 32 + 1) * 32,32,32 }))
			{
				return true;
			}
		}
		if (Level[(size_t)((y) / 32)][(size_t)(x / 32 + 1)].ID == 1)
		{
			if (CheckCollisionRecs(Rectangle{ (float)x , (float)y, 32,32 }, Rectangle{ (float)(x / 32 + 1) * 32,(float)((y) / 32) * 32,32,32 }))
			{
				return true;
			}
		}
		if (Level[(size_t)((y) / 32 + 1)][(size_t)(x / 32 + 1)].ID == 1)
		{
			if (CheckCollisionRecs(Rectangle{ (float)x , (float)y, 32,32 }, Rectangle{ (float)(x / 32 + 1) * 32,(float)((y) / 32 + 1) * 32,32,32 }))
			{
				return true;
			}
		}
		return false;
	}

	void Update()
	{
		int Tmp_x = 0;
		int Tmp_y = 0;
		if ((!IsKeyDown(KEY_W)) && Tmp_y < 191)
		{
			//Tmp_y += 2;
		}
		if (IsKeyDown(KEY_A) && x > 1)
		{
			Tmp_x-=2;
		}
		if (IsKeyDown(KEY_D) && x < 191)
		{
			Tmp_x+=2;
		}
		if (IsKeyDown(KEY_W) && y > 4)
		{
			Tmp_y-=5;
		}
		if (IsKeyDown(KEY_S) && y < 191)
		{
			Tmp_y+=2;
		}
		bool collides = false;
		while (Tmp_y > 0)
		{
			if (!Fourcollision(x, y + 1))	{Tmp_y--; y++;}
			else
				break;
		}
		while (Tmp_y < 0)
		{
			if (!Fourcollision(x, y - 1))	{Tmp_y++; y--;}
			else
				break;
		}
		while (Tmp_x > 0)
		{
			if (!Fourcollision(x +1 , y))	{ Tmp_x--; x++;}
			else
				break;
			
		}
		while (Tmp_x < 0)
		{
			if (!Fourcollision(x - 1, y))	{Tmp_x++; x--;}
			else
				break;
		}
	}

	void Draw()
	{
		DrawText((std::to_string(x / 32) + "|" + std::to_string(y / 32)).c_str(), 0,0,20,BLACK);
		DrawRectangleLines(x / 32 * 32			, y / 32 * 32, 32, 32, BLUE);
		DrawRectangleLines(x / 32 * 32 + 32		, y / 32 * 32, 32, 32, BLUE);
		DrawRectangleLines(x / 32 * 32 + 32		, y / 32 * 32 + 32, 32, 32, BLUE);
		DrawRectangleLines(x / 32 * 32			, y / 32 * 32 +32, 32, 32, BLUE);
		DrawRectangle(x, y, 32, 32, Color{0,255,0,128});
	}
	Player();
	~Player();

private:

};

Player::Player()
{
}

Player::~Player()
{
}

int main()
{
	Player player;
	InitWindow(256, 256,"Plugin Prototype");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	while (! WindowShouldClose())
	{
		player.Update();
		BeginDrawing();
		ClearBackground(WHITE);
		player.Draw();
		DrawFPS(0,32);
		for (uint8_t it_Y = 0; it_Y < 7; it_Y++)
		{
			for (uint8_t it_X = 0; it_X < 7; it_X++)
			{
				switch (Level[it_Y][it_X].ID)
				{
				case 0:
					break;
				case 1:
					DrawRectangle(it_X * 32, it_Y * 32, 32, 32, Level[it_Y][it_X].COL);
					break;
				case 2:
					DrawTriangle
					(
						Vector2{ (float)it_X * 32, (float)it_Y * 32 + 32 },
						Vector2{ (float)it_X * 32 + 32 , (float)it_Y * 32 + 32 },
						Vector2{ (float)it_X * 32 + 32, (float)it_Y * 32 },
						Level[it_Y][it_X].COL
					);
					break;
				case 3:
					DrawTriangle
					(
						Vector2{ (float)it_X * 32 + 32, (float)it_Y * 32 + 32 },
						Vector2{ (float)it_X * 32 + 32, (float)it_Y * 32 },
						Vector2{ (float)it_X * 32, (float)it_Y * 32 },
						Level[it_Y][it_X].COL
					);
					break;
				case 4:
					DrawTriangle
					(
						Vector2{ (float)it_X * 32 + 32, (float)it_Y * 32},
						Vector2{ (float)it_X * 32, (float)it_Y * 32},
						Vector2{ (float)it_X * 32, (float)it_Y * 32 + 32 },
						Level[it_Y][it_X].COL
					);
					break;
				case 5:
					DrawTriangle
					(
						Vector2{ (float)it_X * 32, (float)it_Y * 32 },
						Vector2{ (float)it_X * 32, (float)it_Y * 32 + 32 },
						Vector2{ (float)it_X * 32 + 32 , (float)it_Y * 32 + 32 },
						Level[it_Y][it_X].COL
					);
					break;
				default:
					break;
				}
			}
		}

		EndDrawing();
	}

	CloseWindow();
}
