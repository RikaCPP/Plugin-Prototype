#include"Loader.h"
#include<raylib.h>
#include<stdint.h>
#include<string>
#include<vector>
#include<iostream>

struct sCheckAreaLRUD
{
	int MostLeftCheck = 0;
	int MostRightCheck = 0;
	int MostUpCheck = 0;
	int MostDownCheck = 0;
};

struct Collider
{
	sCheckAreaLRUD StaticArea;
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
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},1}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},2}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},},
	{{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0},	{{255,0,0,128},0}, {{255,0,0,128},0}, {{255,0,0,128},0},}
};

class Player
{
public:
	int x = 0;
	int y = 16;
	std::vector<Rectangle> HitBox;
	Collider CollisionBox {sCheckAreaLRUD{0,1,0,2},Rectangle{0,0,16,18}};
	
	enum class eAxis{X, Y};

	bool Fourcollision(int x, int y, int &Tmp_x, int &Tmp_y, eAxis Axis, bool CalledFromFourcollision)
	{
		struct sCorseXY
			{
				int x;
				int y;
			}; sCorseXY CorseXY = { (x + CollisionBox.CollisionBoxNotStatic.x) / 16,(y + CollisionBox.CollisionBoxNotStatic.y) / 16 };
			for (int ycount = CollisionBox.StaticArea.MostUpCheck; ycount <= CollisionBox.StaticArea.MostDownCheck; ycount++)
			{
				for (int xcount = CollisionBox.StaticArea.MostLeftCheck; xcount <= CollisionBox.StaticArea.MostRightCheck; xcount++)
				{
					DrawRectangle(
						(float)(CorseXY.x + xcount) * 16, 
						(float)(CorseXY.y + ycount) * 16, 16, 16, GRAY);
					DrawRectangle(
						(float)x + CollisionBox.CollisionBoxNotStatic.x,
						(float)y + CollisionBox.CollisionBoxNotStatic.y,
						CollisionBox.CollisionBoxNotStatic.width,
						CollisionBox.CollisionBoxNotStatic.height,
						DARKBROWN);
					if (CorseXY.y + ycount < 7 && CorseXY.y + ycount >= 0 && CorseXY.x + xcount < 7 && CorseXY.x + xcount >= 0)
					{

						switch (Level[CorseXY.y + ycount][CorseXY.x + xcount].ID)
						{
						case 1:

							if (CheckCollisionRecs(Rectangle{ (float)(CorseXY.x + xcount) * 16,(float)(CorseXY.y + ycount) * 16,16,16 }, Rectangle{ (float)x + CollisionBox.CollisionBoxNotStatic.x,(float)y + CollisionBox.CollisionBoxNotStatic.y,CollisionBox.CollisionBoxNotStatic.width,CollisionBox.CollisionBoxNotStatic.height }))
							{
								return true;
							}
							break;

						case 2:
							if (CheckCollisionRecs(Rectangle{ (float)(CorseXY.x + xcount) * 16,(float)(CorseXY.y + ycount) * 16,16,16 }, Rectangle{ (float)x + CollisionBox.CollisionBoxNotStatic.x,(float)y + CollisionBox.CollisionBoxNotStatic.y,CollisionBox.CollisionBoxNotStatic.width,CollisionBox.CollisionBoxNotStatic.height }))
							{
								
									if (((y + CollisionBox.CollisionBoxNotStatic.y + CollisionBox.CollisionBoxNotStatic.height > ((CorseXY.y + ycount + 1) * 16)) || (x + CollisionBox.CollisionBoxNotStatic.x + CollisionBox.CollisionBoxNotStatic.width > ((CorseXY.x + xcount + 1) * 16))))
									{
										if (Axis == eAxis::X && Tmp_x > 0)
										{
											Tmp_y = -1;
										}
										return true;
									}
									else if
										(
											(int)(x + CollisionBox.CollisionBoxNotStatic.x + CollisionBox.CollisionBoxNotStatic.width - ((CorseXY.x + xcount) * 16)
												+ y + CollisionBox.CollisionBoxNotStatic.y + CollisionBox.CollisionBoxNotStatic.height - ((CorseXY.y + ycount) * 16)) >= 18
											)
									{
										DrawRectangle(0, 0, 8, 8, RED);

										Tmp_y = -1;


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
		return false;
	}

	void Update()
	{
		int Tmp_x = 0;
		int Tmp_y = 0;
		Fourcollision(x, y, Tmp_x, Tmp_y, eAxis::X, false);
		//if (y < 102) { Tmp_y += 2; }
		if (IsKeyDown(KEY_A) && x > -8){Tmp_x-=2;}
		if (IsKeyDown(KEY_D) && x < 102){Tmp_x+=2;}
		if (IsKeyDown(KEY_W) && y > -6){Tmp_y-=5;}
		if (IsKeyDown(KEY_S) && y < 102){Tmp_y+=2;}
			while (Tmp_x > 0)
			{
				if (!Fourcollision(x + 1, y, Tmp_x, Tmp_y, eAxis::X, false)) { Tmp_x--; x++; }
				else break;
			}
			while (Tmp_x < 0)
			{
				if (!Fourcollision(x - 1, y, Tmp_x, Tmp_y, eAxis::X, false)) { Tmp_x++; x--; }
				else break;
			}
			while (Tmp_y > 0)
			{
				if (!Fourcollision(x, y + 1, Tmp_x, Tmp_y, eAxis::Y, false)) { Tmp_y--; y++; }
				else break;
			}
			while (Tmp_y < 0)
			{
				if (!Fourcollision(x, y - 1, Tmp_x, Tmp_y, eAxis::Y, false)) { Tmp_y++; y--; }
				else break;
			}

			
	}

	void Draw()
	{
		//DrawLine(x+400	,y		,	x	- 400	, y			,GRAY);
		//DrawLine(x		,y+400	,	x			,	y-400	,GRAY);
		DrawText((std::to_string(x / 16) + "|" + std::to_string(y / 16)).c_str(), 0,0,20,WHITE);
		bool isFirst = true;
			DrawRectangle(x + CollisionBox.CollisionBoxNotStatic.x, y + CollisionBox.CollisionBoxNotStatic.y, CollisionBox.CollisionBoxNotStatic.width, CollisionBox.CollisionBoxNotStatic.height, Color{ 0,255,0,128 });
			for (int ycount = CollisionBox.StaticArea.MostUpCheck; ycount <= CollisionBox.StaticArea.MostDownCheck; ++ycount)
			{
				for (int xcount = CollisionBox.StaticArea.MostLeftCheck; xcount <= CollisionBox.StaticArea.MostRightCheck; ++xcount)
				{
					if (isFirst == true)
					{
						//DrawRectangleLines(x / 16 * 16 + xcount * 16, y / 16 * 16 + ycount * 16, 16, 16, Color{ 0,0,255,200 });
					}
					else
					{
						//DrawRectangleLines(x / 16 * 16 + xcount * 16, y / 16 * 16 + ycount * 16, 16, 16, Color{0,255,255,200});
					}
				}
			}
			isFirst = false;
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
		BeginDrawing();
		ClearBackground(WHITE);
		BeginTextureMode(IngameRenderer);
		player.Update();
		ClearBackground(BLACK);
		player.Draw();
		//DrawFPS(0,32);
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
