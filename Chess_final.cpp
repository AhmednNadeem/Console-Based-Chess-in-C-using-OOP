//--Complete game
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <Windows.h>
using namespace std;
string setfullname(char c, char g, int n);
int input(int a, int b);
void nextturn();
struct position
{
	int x; int y;
};
struct BOTij
{
	int i, j;
	char color;
	string name;
};
BOTij findbot(int x, int y);
class goti
{
public:
	goti()
	{
		currentposition.x = -1;
		currentposition.y = -1;
	}
	void die()
	{
		currentposition.x = -1;
		currentposition.y = -1;
	}
	void printerror()
	{
		cout << "Invalid Inputs \tEnter Again\n";
		Sleep(1500);
	}
	position getposition()
	{
		return currentposition;
	}
	string getname()
	{
		return fullname;
	}
	char getcolor()
	{
		return(fullname[0]);
	}
	virtual int move(int x, int y, char c) = 0;
protected:
	position currentposition;
	string fullname;
	char name;
};
goti ***bots;
class king :public goti
{
private:
public:
	king() {	}
	king(char t)
	{
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 7;
			fullname = "B K ";
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 0;
			fullname = "W K ";
		}

		currentposition.y = 3;
		name = 'K';
	}
	int move(int x, int y, char c)
	{
		if ((x == (currentposition.x)) || ((x == (currentposition.x - 1)) && (y == (currentposition.y + 1))) || ((x == (currentposition.x - 1)) && (y == (currentposition.y - 1))) ||
			((x == (currentposition.x + 1)) && (y == (currentposition.y - 1))) || (y == (currentposition.y + 1)) || (y == (currentposition.y + 1)) || (x == (currentposition.x - 1))
			|| ((x == (currentposition.x + 1)) && (y == (currentposition.y + 1))))
		{
			kill(x, y);
			currentposition.x = x;
			currentposition.y = y;
			return 1;
		}
		return -1;
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
	position getposition()
	{
		return currentposition;
	}
	string getname()
	{
		return fullname;
	}
	char getcolor()
	{
		return(fullname[0]);
	}
};
class queen :public goti
{
private:
	static int countblack;
	static int countwhite;
public:
	queen() {	}
	queen(char t)
	{
		if (t == 'B' || t == 'b')
		{
			countblack++;
			currentposition.x = 7;
			fullname = setfullname('B', 'Q', countblack);
		}
		if (t == 'W' || t == 'w')
		{
			countwhite++;
			currentposition.x = 0;
			fullname = setfullname('W', 'Q', countwhite);
		}

		currentposition.y = 4;
	}
	queen(char t, int x, int y)
	{
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 0;
			countblack++;
			fullname = setfullname('B', 'Q', countblack);
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 7;
			countwhite++;
			fullname = setfullname('W', 'Q', countwhite);
		}
		currentposition.y = y;
		cout << "queen contructor\n";
	}
	int move(int x, int y, char c)
	{
		int ix1, iy1, ix2, iy2;
		int fx1, fy1, fx2, fy2;

		int fromX, fromY, toX, toY; BOTij check;

		for (ix1 = currentposition.x, iy1 = currentposition.y; (ix1 > 0 && iy1 > 0); ix1--, iy1--) {}
		for (fx1 = currentposition.x, fy1 = currentposition.y; (fx1 < 7 && fy1 < 7); fx1++, fy1++) {}

		for (ix2 = currentposition.x, iy2 = currentposition.y; (ix2 > 0 && iy2 < 7); ix2--, iy2++) {}
		for (fx2 = currentposition.x, fy2 = currentposition.y; (fx2 < 7 && fy2 > 0); fx2++, fy2--) {}

		for (int i = ix1, j = iy1; i <= fx1, j <= fy1; i++, j++)
		{
			if (x == i && y == j)
			{
				if (currentposition.x < x) { fromX = currentposition.x + 1; fromY = currentposition.y + 1; toX = x - 1, toY = y - 1; }
				if (currentposition.x > x) { fromX = x + 1; fromY = y + 1; toX = currentposition.x - 1, toY = currentposition.y - 1; }
				for (int a = fromX, b = fromY; a <= toX; a++, b++)
				{
					check = findbot(a, b);
					if (check.i != -1) { cout << "occupied\n"; return -1; }
				}
				kill(x, y);
				currentposition.x = x;
				currentposition.y = y;
				return 1;
			}
		}
		for (int i = ix2, j = iy2; i <= fx2, j >= fy2; i++, j--)
		{
			if (x == i && y == j)
			{
				if (currentposition.x < x) { fromX = currentposition.x + 1; fromY = currentposition.y - 1; toX = x - 1, toY = y + 1; }
				if (currentposition.x > x) { fromX = x + 1; fromY = y - 1; toX = currentposition.x - 1, toY = currentposition.y + 1; }
				for (int a = fromX, b = fromY; a <= toX; a++, b--)
				{
					check = findbot(a, b);
					if (check.i != -1) { cout << "occupied\n"; return -1; }
				}
				kill(x, y);
				currentposition.x = x;
				currentposition.y = y;
				return 1;
			}
		}
		int from, to;
		if (x == currentposition.x)
		{
			if (currentposition.y < y) { from = currentposition.y + 1; to = y - 1; }
			if (currentposition.y > y) { from = y + 1; to = currentposition.y - 1; }
			for (int i = from; i <= to; i++)
			{
				check = findbot(x, i);
				if (check.i != -1) { cout << "occupied\n"; return -1; }
			}
		}
		if (y == currentposition.y)
		{
			if (currentposition.x < x) { from = currentposition.x + 1; to = x - 1; }
			if (currentposition.x > x) { from = x + 1; to = currentposition.x - 1; }
			for (int i = from; i <= to; i++)
			{
				check = findbot(i, y);
				if (check.i != -1) { cout << "occupied\n"; return -1; }
			}
		}
		if (x == currentposition.x || y == currentposition.y)
		{
			kill(x, y);
			currentposition.x = x;
			currentposition.y = y;
			return 1;
		}
		return -1;
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
};
class rook :public goti
{
private:
	static int countblack;
	static int countwhite;
public:
	rook() {	}
	rook(char t, int n)
	{
		if (t == 'B' || t == 'b')
		{
			countblack++;
			currentposition.x = 7;
		}
		if (t == 'W' || t == 'w')
		{
			countwhite++;
			currentposition.x = 0;
		}
		if (n == 1)
		{
			currentposition.y = 0;
		}
		if (n == 2)
		{
			currentposition.y = 7;
		}
		fullname = setfullname(t, 'R', n);
		name = 'R';
	}
	rook(char t, int x, int y)
	{
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 0;
			countblack++;
			fullname = setfullname('B', 'R', countblack);
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 7;
			countwhite++;
			fullname = setfullname('W', 'R', countwhite);
		}
		currentposition.y = y;
	}
	int move(int x, int y, char c)
	{
		int from, to;
		BOTij check;
		if (x == currentposition.x)
		{
			if (currentposition.y < y)
			{
				from = currentposition.y + 1;
				to = y - 1;
			}
			if (currentposition.y > y)
			{
				from = y + 1;
				to = currentposition.y - 1;
			}
			for (int i = from; i <= to; i++)
			{
				check = findbot(x, i);
				if (check.i != -1) { cout << "occupied\n"; return -1; }
			}
		}
		if (y == currentposition.y)
		{
			if (currentposition.x < x) { from = currentposition.x + 1; to = x - 1; }
			if (currentposition.x > x) { from = x + 1; to = currentposition.x - 1; }
			for (int i = from; i <= to; i++)
			{
				check = findbot(i, y);
				if (check.i != -1) { cout << "occupied\n"; return -1; }
			}
		}
		if (x == currentposition.x || y == currentposition.y)
		{
			kill(x, y);
			currentposition.x = x;
			currentposition.y = y;
			return 1;
		}
		return -1;
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
};
class bishop :public goti
{
private:
	static int countblack;
	static int countwhite;
public:
	bishop() {	}
	bishop(char t, int n)
	{
		if (t == 'B' || t == 'b')
		{
			countblack++;
			currentposition.x = 7;
		}
		if (t == 'W' || t == 'w')
		{
			countwhite++;
			currentposition.x = 0;
		}
		if (n == 1)
		{
			currentposition.y = 2;
		}
		if (n == 2)
		{
			currentposition.y = 5;
		}
		name = 'B';
		fullname = setfullname(t, name, n);
	}
	bishop(char t, int x, int y)
	{
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 0;
			countblack++;
			fullname = setfullname('B', 'B', countblack);
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 7;
			countwhite++;
			fullname = setfullname('W', 'B', countwhite);
		}
		currentposition.y = y;
	}
	int move(int x, int y, char c)
	{
		int ix1, iy1;
		int fx1, fy1;

		int ix2, iy2;
		int fx2, fy2;

		int fromX, fromY, toX, toY; BOTij check;

		for (ix1 = currentposition.x, iy1 = currentposition.y; (ix1 > 0 && iy1 > 0); ix1--, iy1--) {}
		for (fx1 = currentposition.x, fy1 = currentposition.y; (fx1 < 7 && fy1 < 7); fx1++, fy1++) {}

		for (ix2 = currentposition.x, iy2 = currentposition.y; (ix2 > 0 && iy2 < 7); ix2--, iy2++) {}
		for (fx2 = currentposition.x, fy2 = currentposition.y; (fx2 < 7 && fy2 > 0); fx2++, fy2--) {}

		for (int i = ix1, j = iy1; i <= fx1, j <= fy1; i++, j++)
		{
			if (x == i && y == j)
			{
				if (currentposition.x < x) { fromX = currentposition.x + 1; fromY = currentposition.y + 1; toX = x - 1, toY = y - 1; }
				if (currentposition.x > x) { fromX = x + 1; fromY = y + 1; toX = currentposition.x - 1, toY = currentposition.y - 1; }
				for (int a = fromX, b = fromY; a <= toX; a++, b++)
				{
					check = findbot(a, b);
					if (check.i != -1) { cout << "occupied 1\n";  return -1; }
				}
				kill(x, y);
				currentposition.x = x, currentposition.y = y;
				return 1;
			}
		}
		for (int i = ix2, j = iy2; i <= fx2, j >= fy2; i++, j--)
		{
			if (x == i && y == j)
			{
				if (currentposition.x < x) { fromX = currentposition.x + 1; fromY = currentposition.y - 1; toX = x - 1, toY = y + 1; }
				if (currentposition.x > x) { fromX = x + 1; fromY = y - 1; toX = currentposition.x - 1, toY = currentposition.y + 1; }
				for (int a = fromX, b = fromY; a <= toX; a++, b--)
				{
					check = findbot(a, b);
					if (check.i != -1) { cout << "occupied 2\n";  return -1; }
				}
				kill(x, y);
				currentposition.x = x, currentposition.y = y;
				return 1;
			}
		}
		return -1;
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
};
class knight :public goti
{
private:
	static int countblack;
	static int countwhite;
public:
	knight() {	}
	knight(char t, int n)
	{
		if (t == 'B' || t == 'b')
		{
			countblack++;
			currentposition.x = 7;
		}
		if (t == 'W' || t == 'w')
		{
			countwhite++;
			currentposition.x = 0;
		}
		if (n == 1)
		{
			currentposition.y = 1;
		}
		if (n == 2)
		{
			currentposition.y = 6;
		}
		name = 'k';
		fullname = setfullname(t, name, n);
	}
	knight(char t, int x, int y)
	{
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 0;
			countblack++;
			fullname = setfullname('B', 'K', countblack);
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 7;
			countwhite++;
			fullname = setfullname('W', 'K', countwhite);
		}
		currentposition.y = y;
	}
	int move(int x, int y, char c)
	{
		if (((x == (currentposition.x + 2)) && (y == (currentposition.y + 1))) || ((x == (currentposition.x + 2)) && ((currentposition.y - 1) == y)) ||
			((x == (currentposition.x - 2)) && (y == (currentposition.y - 1))) || ((x == (currentposition.x - 2))) && ((y == (currentposition.y + 1))) ||
			((x == (currentposition.x + 1)) && (y == (currentposition.y - 2))) || ((x == (currentposition.x + 1)) && (y == (currentposition.y + 2))) ||
			((x == (currentposition.x - 1)) && (y == (currentposition.y - 2))) || ((x == (currentposition.x - 1)) && (y == (currentposition.y + 2))))
		{
			kill(x, y);
			currentposition.x = x;
			currentposition.y = y;
			return 1;
		}
		return -1;
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
};
class pawn :public goti
{
private:
	int firstmove;
public:
	pawn() {	}
	pawn(char t, int n)
	{
		firstmove = 0;
		if (t == 'B' || t == 'b')
		{
			currentposition.x = 6;
		}
		if (t == 'W' || t == 'w')
		{
			currentposition.x = 1;
		}
		currentposition.y = n - 1;
		////////////////////////////////////-------------delete
		/*if ((t == 'W' || t == 'w') && n == 2)
		{
			currentposition.x = 3;
			currentposition.y = 7;
		}
		if ((t == 'B' || t == 'b') && n == 2)
		{
			currentposition.x = 2;
			currentposition.y = 1;
		}*/
		//////////////////////////////////////-------------delete
		name = 'P';
		fullname = setfullname(t, name, n);
	}
	int move(int x, int y, char c)
	{
		BOTij check;
		if (c == 'W' || c == 'w')
		{
			if ((y == currentposition.y + 1 || y == currentposition.y - 1) && (x == currentposition.x + 1))
			{
				check = findbot(x, y);
				if (check.i == -1) { return -1; }
				kill(x, y);

				currentposition.x = x;
				currentposition.y = y;
				firstmove = 1;
				if (currentposition.x == 7)
					transform();
				return 1;

			}
			else
			{
				if ((y == currentposition.y) && ((firstmove == 1 && x == (currentposition.x + 1)) || (firstmove == 0 && (x == (currentposition.x + 1)
					|| x == (currentposition.x + 2)))))
				{
					if (currentposition.x + 1 == x)
					{
						check = findbot(x, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
					}
					if (currentposition.x + 2 == x)
					{
						check = findbot(x, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
						check = findbot(x - 1, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
					}
					currentposition.x = x;
					currentposition.y = y;
					firstmove = 1;
					if (currentposition.x == 7)
						transform();
					return 1;
				}
			}
		}

		if (c == 'b' || c == 'B')
		{
			if ((y == currentposition.y + 1 || y == currentposition.y - 1) && (x == currentposition.x - 1))
			{
				check = findbot(x, y);
				if (check.i == -1) { return -1; }
				kill(x, y);

				currentposition.x = x;
				currentposition.y = y;
				firstmove = 1;
				if (currentposition.x == 0)
					transform();
				return 1;
			}
			else
			{
				if ((y == currentposition.y) && ((firstmove == 1 && x == (currentposition.x - 1)) || (firstmove == 0 && (x == (currentposition.x - 1)
					|| x == (currentposition.x - 2)))))
				{
					if (currentposition.x - 1 == x)
					{
						check = findbot(x, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
					}
					if (currentposition.x - 2 == x)
					{
						check = findbot(x, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
						check = findbot(x + 1, y);
						if (check.i != -1) { cout << "Occupied\n"; return -1; }
					}
					currentposition.x = x;
					currentposition.y = y;
					firstmove = 1;
					if (currentposition.x == 0)
						transform();
					return 1;
				}
			}
		}
	}
	void kill(int x, int y)
	{
		BOTij todie;
		todie = findbot(x, y);
		if (todie.i != -1)
		{
			bots[todie.i][todie.j]->die();
		}
	}
	void transform()
	{
		int color = -1, bot = -1;
		char c; c = fullname[0];
		int choice;
		bot = (fullname[3] - '0') + 7;
		if (fullname[0] == 'B' && currentposition.x == 0)
		{
			color = 0;
			delete bots[0][bot];
		}

		if (fullname[0] == 'W' && currentposition.x == 7)
		{
			color = 1;
			delete bots[1][bot];
		}
		cout << "\t\tPromotion\nEnter Following\n1 To Transform Into Queen\n2 To Transform Into Rook\n3 To Transform Into Bishop\n4 To Transform Into Knight\n";
		cout << "Enter : ";
		choice = input(1, 4);
		switch (choice)
		{
		case 1:
		{
			bots[color][bot] = new queen(c, currentposition.x, currentposition.y);
			break;
		}
		case 2:
		{
			bots[color][bot] = new rook(c, currentposition.x, currentposition.y);
			break;
		}
		case 3:
		{
			bots[color][bot] = new bishop(c, currentposition.x, currentposition.y);
			break;
		}
		case 4:
		{
			bots[color][bot] = new knight(c, currentposition.x, currentposition.y);
			break;
		}

		}
		cout << "Transformation Successful \n";
		Sleep(1000);
	}
};
int queen::countwhite = 0;
int queen::countblack = 0;
int rook::countwhite = 0;
int rook::countblack = 0;
int bishop::countwhite = 0;
int bishop::countblack = 0;
int knight::countwhite = 0;
int knight::countblack = 0;
void InitializeBots();
void printboard(int p = 1);
int endgame();
int main()
{
	InitializeBots();
	int xi, xf, yi, yf, player = 1;

	position match;
	BOTij go, on;

	while (1) {
		printboard(player);
		nextturn();

		while (1) {
			while (1) {
				while (1) {
					cout << "\t\tEnter Piece to move \n";
					cout << "Enter Row of Piece : ";
					xi = input(0, 7);
					cout << "Enter Coloum of Piece : ";
					yi = input(0, 7);
					go = findbot(xi, yi);
					if (go.color != 'G' && go.i == player - 1)
						break;
					cout << "\tInvalid Input \tEnter Again \n";
				}
				cout << "\n\t\tEnter Where to move \n";
				cout << "Enter Row : ";
				xf = input(0, 7);
				cout << "Enter Coloum : ";
				yf = input(0, 7);

				on = findbot(xf, yf);
				if (toupper(go.color) != toupper(on.color))
					break;
				cout << "\tOccupied Block \tEnter Again\n";
			}
			if (bots[go.i][go.j]->move(xf, yf, go.color) == 1)
				break;
			cout << "\tInvalid Inputs\tEnter Again\n";
		}
		player++;
		player = (player == 3 ? 1 : 2);
		system("cls");
		if (endgame() != -1)break;
	}
	printboard();
	if (endgame() == 1) { cout << "\t\tPlayer 2 Won\n"; }
	if (endgame() == 2) { cout << "\t\tPlayer 1 Won\n"; }
	cout << "Game Ended\n";
	Sleep(1000);
	system("pause");
}
string setfullname(char c, char g, int n)
{
	c = toupper(c);
	g = toupper(g);
	string name = "W B1";
	name[0] = c;
	name[2] = g;
	name[3] = n + '0';
	return name;
}
void printboard(int p)
{
	BOTij check;
	for (int i = 0; i < 8; i++)
	{
		if (i == 0) { cout << " _______________________________________________________________ \n"; }
		else
		{
			cout << "|_______|_______|_______|_______|_______|_______|_______|_______|\n";
		}
		cout << "|       |       |       |       |       |       |       |       |\n";
		for (int j = 0; j < 8; j++)
		{
			cout << "| ";
			check = findbot(i, j);
			cout << check.name;
			cout << "  ";
			if (j == 7) { cout << "|----" << i << "\n"; }
		}
		if (i == 7)
		{
			cout << "|_______|_______|_______|_______|_______|_______|_______|_______|\n";
			cout << "    0       1       2       3       4       5       6       7\n";
		}
	}
	cout << "\t\tPLAYER " << p << " TURN ( ";
	if (p == 1)cout << "Black )\n";
	else cout << "White )\n";
}
void InitializeBots()
{
	bots = new goti**[2];
	bots[0] = new goti*[16];			bots[1] = new goti*[16];

	bots[0][0] = new king('b');			bots[0][1] = new queen('b');
	bots[0][2] = new rook('b', 1);		bots[0][3] = new rook('b', 2);
	bots[0][4] = new bishop('b', 1);	bots[0][5] = new bishop('b', 2);
	bots[0][6] = new knight('b', 1);	bots[0][7] = new knight('b', 2);
	for (int i = 8; i <= 15; i++) { bots[0][i] = new pawn('b', i - 7); }

	bots[1][0] = new king('w');			bots[1][1] = new queen('w');
	bots[1][2] = new rook('w', 1);		bots[1][3] = new rook('w', 2);
	bots[1][4] = new bishop('w', 1);	bots[1][5] = new bishop('w', 2);
	bots[1][6] = new knight('w', 1);	bots[1][7] = new knight('w', 2);
	for (int i = 8; i <= 15; i++) { bots[1][i] = new pawn('w', i - 7); }
}
BOTij findbot(int x, int y)
{
	BOTij bot;
	bot.i = -1, bot.j = -1, bot.color = 'G', bot.name = "    ";
	position match;
	char color; string name;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			name = bots[i][j]->getname();
			match = bots[i][j]->getposition();
			color = bots[i][j]->getcolor();
			if (match.x == x && match.y == y)
			{
				bot.i = i;
				bot.j = j;
				bot.color = color;
				bot.name = name;
				return bot;
			}
		}
	}
	return bot;
}
int input(int a, int b)
{
	int x;
	do {
		cin >> x;
		if (x >= a && x <= b)
		{
			break;
		}
		cout << "Invalid Input\tEnter Again : ";
	} while (1);
	return x;
}
void nextturn()
{
	//first back second font
	static int turn = 0;
	if (turn == 0)
	{
		system("COLOR 30");
		turn = 1;
	}
	else
	{
		system("COLOR 3F");
		turn = 0;
	}
}
int endgame()
{
	position check;
	for (int i = 0; i <= 1; i++)
	{
		check = bots[i][0]->getposition();
		if (check.x == -1 && check.y == -1) { return i + 1; }
	}
	return -1;
}