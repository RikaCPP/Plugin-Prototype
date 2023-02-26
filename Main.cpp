#include"Loader.h"
#include<raylib.h>
#include<stdint.h>
#include<string>
#include<vector>
#include<iostream>

struct sCheckArea
{
	int MostLeftCheck = 0;
	int MostRightCheck = 0;
	int MostUpCheck = 0;
	int MostDownCheck = 0;
};

struct Collider
{
	sCheckArea StaticArea;
	Rectangle CollisionBoxNotStatic;
};

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
	int y = 16;
	std::vector<Rectangle> HitBox;
	std::vector<Collider> CollisionBox
	{	
		{sCheckArea{0,1,0,1},Rectangle{0,0,16,16}},
		{sCheckArea{0,1,-1,0},Rectangle{2,-12,12,12}}
	};

	bool Fourcollision(int x, int y, int &Tmp_x, int &Tmp_y, bool CalledFromFourcollision)
	{
		struct sCorseXY
		{
			int x;
			int y;
		}; sCorseXY CorseXY = {x/16,y/16 };
		bool IsFirstCollider = true;
		for (auto &it : CollisionBox)
		{

			for (int ycount = it.StaticArea.MostUpCheck; ycount <= it.StaticArea.MostDownCheck; ycount++)
			{
				for (int xcount = it.StaticArea.MostLeftCheck; xcount <= it.StaticArea.MostRightCheck; xcount++)
				{
					if (CorseXY.y + ycount < 7 && CorseXY.y + ycount >= 0 && CorseXY.x + xcount < 7 && CorseXY.x + xcount >= 0)
					{

						switch (Level[CorseXY.y + ycount][CorseXY.x + xcount].ID)
						{
						case 1:

							if (CheckCollisionRecs(Rectangle{ (float)CorseXY.x * 16 + xcount * 16,(float)CorseXY.y * 16 + ycount * 16,16,16 }, Rectangle{ (float)x + it.CollisionBoxNotStatic.x,(float)y + it.CollisionBoxNotStatic.y,it.CollisionBoxNotStatic.width,it.CollisionBoxNotStatic.height }))
							{
								return true;
							}
							break;

						case 2:
								if (IsFirstCollider)
								{
									if(y + it.CollisionBoxNotStatic.height > ((CorseXY.y + ycount +1)*16)-1)
									{
										return true;
									}
									else if ((int)(x + it.CollisionBoxNotStatic.x + it.CollisionBoxNotStatic.width- ((CorseXY.x+1)*16) +y + it.CollisionBoxNotStatic.y + it.CollisionBoxNotStatic.height - ((CorseXY.y+1) * 16)) >=17)
									{
										return true;
									}
								}
								else
								{
									if (y + it.CollisionBoxNotStatic.height > ((CorseXY.y + ycount + 1) * 16)-1)
									{
										return true;
									}
									else if ((int)(x + it.CollisionBoxNotStatic.x + it.CollisionBoxNotStatic.width - ((CorseXY.x+1) * 16) + y + it.CollisionBoxNotStatic.y + it.CollisionBoxNotStatic.height - ((CorseXY.y+1) * 16)) >= 17)
									{
										return true;
									}
								}
							break;
						default:
							break;
						}
					}
				}
			}
			IsFirstCollider = false;
		}
		return false;
	}

	void Update()
	{
		int Tmp_x = 0;
		int Tmp_y = 0;
		//if (y < 102) { Tmp_y += 2; }
		if (IsKeyDown(KEY_A) && x > -8){Tmp_x-=2;}
		if (IsKeyDown(KEY_D) && x < 102){Tmp_x+=2;}
		if (IsKeyDown(KEY_W) && y > -6){Tmp_y-=5;}
		if (IsKeyDown(KEY_S) && y < 102){Tmp_y+=2;}
		while (Tmp_x > 0)
		{
			if (!Fourcollision(x + 1, y, Tmp_x, Tmp_y, false)) { Tmp_x--; x++; }
			else break;
		}
		while (Tmp_x < 0)
		{
			if (!Fourcollision(x - 1, y, Tmp_x, Tmp_y, false)) { Tmp_x++; x--; }
			else break;
		}
		while (Tmp_y > 0)
		{
			if (!Fourcollision(x, y + 1, Tmp_x, Tmp_y,false))	{Tmp_y--; y++;}
			else break;
		}
		while (Tmp_y < 0)
		{
			if (!Fourcollision(x, y - 1, Tmp_x, Tmp_y, false))	{Tmp_y++; y--;}
			else break;
		}
	}

	void Draw()
	{
		DrawText((std::to_string(x / 16) + "|" + std::to_string(y / 16)).c_str(), 0,0,20,WHITE);
		for (Collider &it : CollisionBox)
		{
			DrawRectangle(x + it.CollisionBoxNotStatic.x, y + it.CollisionBoxNotStatic.y, it.CollisionBoxNotStatic.width, it.CollisionBoxNotStatic.height, Color{ 0,255,0,128 });
			for (int ycount = it.StaticArea.MostUpCheck; ycount <= it.StaticArea.MostDownCheck; ++ycount)
			{
				for (int xcount = it.StaticArea.MostLeftCheck; xcount <= it.StaticArea.MostRightCheck; ++xcount)
				{
					DrawRectangleLines(x / 16 * 16 + xcount * 16, y / 16 * 16 + ycount * 16, 16, 16, BLUE);
				}
			}
		}
		/*DrawRectangleLines(x / 16 * 16, y / 16 * 16, 16, 16, BLUE);
		DrawRectangleLines(x / 16 * 16 + 16		, y / 16 * 16, 16, 16, BLUE);
		DrawRectangleLines(x / 16 * 16 + 16		, y / 16 * 16 + 16, 16, 16, BLUE);
		DrawRectangleLines(x / 16 * 16			, y / 16 * 16 +16, 16, 16, BLUE);*/
	}
	Player(){}
	~Player(){}

private:

};

int main()
{
	Player player;
	InitWindow(256, 256,"Plugin Prototype");
	SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	SetTargetFPS(60);
	RenderTexture IngameRenderer = LoadRenderTexture(256,256);
	while (! WindowShouldClose())
	{
		player.Update();
		BeginDrawing();
		ClearBackground(WHITE);
		BeginTextureMode(IngameRenderer);
		ClearBackground(BLACK);
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
					DrawRectangle(it_X * 16, it_Y * 16, 16, 16, Level[it_Y][it_X].COL);
					break;
				case 2:
					DrawTriangle
					(
						Vector2{ (float)it_X * 16, (float)it_Y * 16 + 16 },
						Vector2{ (float)it_X * 16 + 16 , (float)it_Y * 16 + 16 },
						Vector2{ (float)it_X * 16 + 16, (float)it_Y * 16 },
						Level[it_Y][it_X].COL
					);
					break;
				case 3:
					DrawTriangle
					(
						Vector2{ (float)it_X * 16 + 16, (float)it_Y * 16 + 16 },
						Vector2{ (float)it_X * 16 + 16, (float)it_Y * 16 },
						Vector2{ (float)it_X * 16, (float)it_Y * 16 },
						Level[it_Y][it_X].COL
					);
					break;
				case 4:
					DrawTriangle
					(
						Vector2{ (float)it_X * 16 + 16, (float)it_Y * 16},
						Vector2{ (float)it_X * 16, (float)it_Y * 16},
						Vector2{ (float)it_X * 16, (float)it_Y * 16 + 16 },
						Level[it_Y][it_X].COL
					);
					break;
				case 5:
					DrawTriangle
					(
						Vector2{ (float)it_X * 16, (float)it_Y * 16 },
						Vector2{ (float)it_X * 16, (float)it_Y * 16 + 16 },
						Vector2{ (float)it_X * 16 + 16 , (float)it_Y * 16 + 16 },
						Level[it_Y][it_X].COL
					);
					break;
				default:
					break;
				}
			}
		}
		EndTextureMode();
		DrawTexturePro(IngameRenderer.texture, Rectangle{ 0,0,256,-256 }, Rectangle{ 0,0,1024,1024 }, Vector2{0,0},0,WHITE);

		EndDrawing();
	}
	UnloadRenderTexture(IngameRenderer);
	CloseWindow();
}
