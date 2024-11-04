#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Position
const Position Position::npos = Position(-1, -1);

Position::Position(const string &str_pos)
{
    int p = str_pos.find(",");
    string row = str_pos.substr(1, p - 1);
    string col = str_pos.substr(p + 1);
    col.pop_back();
    this->r = stoi(row);
    this->c = stoi(col);
};

// MapElement
MapElement::~MapElement(){};

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    map = new MapElement **[num_rows];
    for (int i = 0; i < num_rows; i++)
        map[i] = new MapElement *[num_cols];

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            map[i][j] = new MapElement(PATH);
        }
    }

    for (int i = 0; i < num_walls; i++)
    {
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        map[row][col] = new MapElement(WALL);
    }

    for (int i = 0; i < num_fake_walls; i++)
    {
        int row = array_fake_walls[i].getRow();
        int col = array_fake_walls[i].getCol();
        map[row][col] = new MapElement(FAKE_WALL);
    }
};

Map::~Map()
{
    for (int i = 0; i < num_rows; i++)
        delete map[i];
    delete map;
};

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
    {
        return false;
    }

    if (map[pos.getRow()][pos.getCol()]->getType() == WALL)
    {
        return false;
    }
    return true;
};

// MovingObject
MovingObject::MovingObject(){};

MovingObject::~MovingObject(){};

// Character
Character::Character(){};

Character::~Character(){};

// Sherlock
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
{
    this->index = index;
    this->moving_rule = moving_rule;
    this->pos = init_pos;
    this->map = map;
    this->hp = init_hp;
    this->exp = init_exp;
    this->name = "Sherlock";
};

Position Sherlock::getNextPosition()
{
    if (moving_rule[step] == 'L')
    {
        if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this))
        {
            return Position(pos.getRow(), pos.getCol() - 1);
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'R')
    {
        if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this))
        {
            return Position(pos.getRow(), pos.getCol() + 1);
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'U')
    {
        if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
        {
            return Position(pos.getRow() - 1, pos.getCol());
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'D')
    {
        if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this))
        {
            return Position(pos.getRow() + 1, pos.getCol());
        }
        return Position::npos;
    }
    return Position::npos;
}

void Sherlock::move()
{
    if (!this->getNextPosition().isEqual(-1, -1))
    {
        if (moving_rule[step] == 'L')
        {
            pos.setCol(pos.getCol() - 1);
        }
        else if (moving_rule[step] == 'R')
        {
            pos.setCol(pos.getCol() + 1);
        }
        else if (moving_rule[step] == 'U')
        {
            pos.setRow(pos.getRow() - 1);
        }
        else if (moving_rule[step] == 'D')
        {
            pos.setRow(pos.getRow() + 1);
        }
    }
    step++;
    if (step >= moving_rule.size())
    {
        step = 0;
    }
}

// Watson
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
{
    this->index = index;
    this->moving_rule = moving_rule;
    this->pos = init_pos;
    this->map = map;
    this->hp = init_hp;
    this->exp = init_exp;
    this->name = "Watson";
};
Position Watson::getNextPosition()
{
    int r = pos.getRow(), c = pos.getCol();
    if (moving_rule[step] == 'L')
    {
        if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this))
        {
            MapElement *p = map->getMovingElement(pos.getRow(), pos.getCol() - 1);
            if ((p->getType() == FAKE_WALL) && (exp <= (r * 257 + (c - 1) * 139 + 89) % 900 + 1))
            {
                return Position::npos;
            }
            return Position(pos.getRow(), pos.getCol() - 1);
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'R')
    {
        if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this))
        {
            MapElement *p = map->getMovingElement(pos.getRow(), pos.getCol() + 1);
            if ((p->getType() == FAKE_WALL) && (exp <= (r * 257 + (c + 1) * 139 + 89) % 900 + 1))
            {
                return Position::npos;
            }
            return Position(pos.getRow(), pos.getCol() + 1);
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'U')
    {
        if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
        {
            MapElement *p = map->getMovingElement(pos.getRow() - 1, pos.getCol());
            if ((p->getType() == FAKE_WALL) && (exp <= ((r - 1) * 257 + (c) * 139 + 89) % 900 + 1))
            {
                return Position::npos;
            }
            return Position(pos.getRow() - 1, pos.getCol());
        }
        return Position::npos;
    }
    if (moving_rule[step] == 'D')
    {
        if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this))
        {
            MapElement *p = map->getMovingElement(pos.getRow() + 1, pos.getCol());
            if ((p->getType() == FAKE_WALL) && (exp <= ((r + 1) * 257 + (c) * 139 + 89) % 900 + 1))
            {
                return Position::npos;
            }
            return Position(pos.getRow() + 1, pos.getCol());
        }
        return Position::npos;
    }
    return Position::npos;
}

void Watson::move()
{
    if (!this->getNextPosition().isEqual(-1, -1))
    {
        if (moving_rule[step] == 'L')
        {
            pos.setCol(pos.getCol() - 1);
        }
        else if (moving_rule[step] == 'R')
        {
            pos.setCol(pos.getCol() + 1);
        }
        else if (moving_rule[step] == 'U')
        {
            pos.setRow(pos.getRow() - 1);
        }
        else if (moving_rule[step] == 'D')
        {
            pos.setRow(pos.getRow() + 1);
        }
    }
    step++;
    if (step >= moving_rule.size())
    {
        step = 0;
    }
}

// Criminal
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->sherlock = sherlock;
    this->watson = watson;
    this->name = "Criminal";
};

Position Criminal::getNextPosition()
{
    int u = space(sherlock->getPos().getRow(), pos.getRow() - 1, sherlock->getPos().getCol(), pos.getCol()) + space(watson->getPos().getRow(), pos.getRow() - 1, watson->getPos().getCol(), pos.getCol());
    int l = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() - 1) + space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() - 1);
    int d = space(sherlock->getPos().getRow(), pos.getRow() + 1, sherlock->getPos().getCol(), pos.getCol()) + space(watson->getPos().getRow(), pos.getRow() + 1, watson->getPos().getCol(), pos.getCol());
    int r = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() + 1) + space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() + 1);

    string moving_rule = "O";
    int lg = -1;

    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
        if (lg < u)
        {
            moving_rule = "U";
            lg = u;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this))
    {
        if (lg < l)
        {
            moving_rule = "L";
            lg = l;
        }
    }

    if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this))
    {
        if (lg < d)
        {
            moving_rule = "D";
            lg = d;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this))
    {
        if (lg < r)
        {
            moving_rule = "R";
            lg = r;
        }
    }

    if (moving_rule[0] == 'L')
    {
        return Position(pos.getRow(), pos.getCol() - 1);
    }
    if (moving_rule[0] == 'R')
    {
        return Position(pos.getRow(), pos.getCol() + 1);
    }
    if (moving_rule[0] == 'U')
    {
        return Position(pos.getRow() - 1, pos.getCol());
    }
    if (moving_rule[0] == 'D')
    {
        return Position(pos.getRow() + 1, pos.getCol());
    }

    return Position::npos;
}

void Criminal::move()
{
    if (!this->getNextPosition().isEqual(-1, -1))
    {
        pre.setRow(pos.getRow());
        pre.setCol(pos.getCol());
        int r = this->getNextPosition().getRow(), c = this->getNextPosition().getCol();
        pos.setRow(r);
        pos.setCol(c);
    }
}

// ArrayMovingObject
ArrayMovingObject::ArrayMovingObject(int capacity)
{
    count = 0;
    this->capacity = capacity;
    arr_mv_objs = new MovingObject *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        arr_mv_objs[i] = nullptr;
    }
};

ArrayMovingObject::~ArrayMovingObject()
{
    delete arr_mv_objs;
};

// Configuration
Configuration::Configuration(const string &filepath)
{
    ifstream fileInput(filepath);

    while (!fileInput.eof())
    {
        char temp[255];
        fileInput.getline(temp, 255);
        string line = temp;

        if (line.find("MAP_NUM_ROWS") == 0)
        {
            map_num_rows = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("MAP_NUM_COLS") == 0)
        {
            map_num_cols = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("MAX_NUM_MOVING_OBJECTS") == 0)
        {
            max_num_moving_objects = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("ARRAY_WALLS") == 0)
        {
            this->num_walls = 0;
            string arr = line.substr(line.find("=") + 1);

            if (arr.find("]") != 1)
            {
                num_walls = 1;
                for (int i = 0; i < arr.size(); i++)
                {
                    if (arr[i] == ';')
                        num_walls++;
                }
            }

            this->arr_walls = new Position[num_walls];

            for (int i = 0; i < num_walls; i++)
            {
                if (arr.find(";") == string::npos)
                {
                    arr_walls[i] = Position(arr.substr(1, arr.find("]") - 1));
                }
                else
                {
                    arr_walls[i] = Position(arr.substr(1, arr.find(";") - 1));
                    arr.erase(1, arr.find(";"));
                }
            }
        }
        else if (line.find("ARRAY_FAKE_WALLS") == 0)
        {
            this->num_fake_walls = 0;
            string arr = line.substr(line.find("=") + 1);

            if (arr.find("]") != 1)
            {
                num_fake_walls = 1;
                for (int i = 0; i < arr.size(); i++)
                {
                    if (arr[i] == ';')
                        num_fake_walls++;
                }
            }

            this->arr_fake_walls = new Position[num_fake_walls];

            for (int i = 0; i < num_fake_walls; i++)
            {
                if (arr.find(";") == string::npos)
                {
                    arr_fake_walls[i] = Position(arr.substr(1, arr.find("]") - 1));
                }
                else
                {
                    arr_fake_walls[i] = Position(arr.substr(1, arr.find(";") - 1));
                    arr.erase(1, arr.find(";"));
                }
            }
        }
        else if (line.find("SHERLOCK_MOVING_RULE") == 0)
        {
            sherlock_moving_rule = line.substr(line.find("=") + 1);
        }
        else if (line.find("SHERLOCK_INIT_POS") == 0)
        {
            sherlock_init_pos = Position(line.substr(line.find("=") + 1));
        }
        else if (line.find("SHERLOCK_INIT_HP") == 0)
        {
            sherlock_init_hp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("SHERLOCK_INIT_EXP") == 0)
        {
            sherlock_init_exp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("WATSON_MOVING_RULE") == 0)
        {
            watson_moving_rule = line.substr(line.find("=") + 1);
        }
        else if (line.find("WATSON_INIT_POS") == 0)
        {
            watson_init_pos = Position(line.substr(line.find("=") + 1));
        }
        else if (line.find("WATSON_INIT_HP") == 0)
        {
            watson_init_hp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("WATSON_INIT_EXP") == 0)
        {
            watson_init_exp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("CRIMINAL_INIT_POS") == 0)
        {
            criminal_init_pos = Position(line.substr(line.find("=") + 1));
        }
        else if (line.find("NUM_STEPS") == 0)
        {
            num_steps = stoi(line.substr(line.find("=") + 1));
        }
    }

    fileInput.close();
};

Configuration::~Configuration()
{
    delete arr_walls;
    delete arr_fake_walls;
};

// Robot
Robot::Robot(){};

Robot::Robot(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
    robot_type = robot_type;
};

Robot::~Robot(){};

// RobotC
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
    robot_type = C;
    name = "C";
};

// RobotS
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
    this->sherlock = sherlock;
    robot_type = S;
    name = "S";
};

Position RobotS::getNextPosition()
{
    int u = space(sherlock->getPos().getRow(), pos.getRow() - 1, sherlock->getPos().getCol(), pos.getCol());
    int l = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() - 1);
    int d = space(sherlock->getPos().getRow(), pos.getRow() + 1, sherlock->getPos().getCol(), pos.getCol());
    int r = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() + 1);

    string moving_rule = "O";
    int sl = -1;

    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
        if (u < sl || sl < 0)
        {
            moving_rule = "U";
            sl = u;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this))
    {
        if (r < sl || sl < 0)
        {
            moving_rule = "R";
            sl = r;
        }
    }

    if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this))
    {
        if (d < sl || sl < 0)
        {
            moving_rule = "D";
            sl = d;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this))
    {
        if (l < sl || sl < 0)
        {
            moving_rule = "L";
            sl = l;
        }
    }

    if (moving_rule[0] == 'L')
    {
        return Position(pos.getRow(), pos.getCol() - 1);
    }
    if (moving_rule[0] == 'R')
    {
        return Position(pos.getRow(), pos.getCol() + 1);
    }
    if (moving_rule[0] == 'U')
    {
        return Position(pos.getRow() - 1, pos.getCol());
    }
    if (moving_rule[0] == 'D')
    {
        return Position(pos.getRow() + 1, pos.getCol());
    }

    return Position::npos;
}

void RobotS::move()
{
    if (!this->getNextPosition().isEqual(-1, -1))
    {
        int r = this->getNextPosition().getRow(), c = this->getNextPosition().getCol();
        pos.setRow(r);
        pos.setCol(c);
    }
}

// RobotW
RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
    this->watson = watson;
    robot_type = W;
    name = "W";
};
Position RobotW::getNextPosition()
{
    int u = space(watson->getPos().getRow(), pos.getRow() - 1, watson->getPos().getCol(), pos.getCol());
    int l = space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() - 1);
    int d = space(watson->getPos().getRow(), pos.getRow() + 1, watson->getPos().getCol(), pos.getCol());
    int r = space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() + 1);

    string moving_rule = "O";
    int sl = -1;

    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this))
    {
        if (u < sl || sl < 0)
        {
            moving_rule = "U";
            sl = u;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this))
    {
        if (r < sl || sl < 0)
        {
            moving_rule = "R";
            sl = r;
        }
    }

    if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this))
    {
        if (d < sl || sl < 0)
        {
            moving_rule = "D";
            sl = d;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this))
    {
        if (l < sl || sl < 0)
        {
            moving_rule = "L";
            sl = l;
        }
    }

    if (moving_rule[0] == 'L')
    {
        return Position(pos.getRow(), pos.getCol() - 1);
    }
    if (moving_rule[0] == 'R')
    {
        return Position(pos.getRow(), pos.getCol() + 1);
    }
    if (moving_rule[0] == 'U')
    {
        return Position(pos.getRow() - 1, pos.getCol());
    }
    if (moving_rule[0] == 'D')
    {
        return Position(pos.getRow() + 1, pos.getCol());
    }

    return Position::npos;
}

void RobotW::move()
{
    if (!this->getNextPosition().isEqual(-1, -1))
    {
        int r = this->getNextPosition().getRow(), c = this->getNextPosition().getCol();
        pos.setRow(r);
        pos.setCol(c);
    }
}

// RobotSW
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    this->index = index;
    this->pos = init_pos;
    this->map = map;
    this->criminal = criminal;
    this->sherlock = sherlock;
    this->watson = watson;
    robot_type = SW;
    name = "SW";
};

Position RobotSW::getNextPosition()
{
    int u = space(sherlock->getPos().getRow(), pos.getRow() - 2, sherlock->getPos().getCol(), pos.getCol()) + space(watson->getPos().getRow(), pos.getRow() - 2, watson->getPos().getCol(), pos.getCol());
    int l = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() - 2) + space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() - 2);
    int d = space(sherlock->getPos().getRow(), pos.getRow() + 2, sherlock->getPos().getCol(), pos.getCol()) + space(watson->getPos().getRow(), pos.getRow() + 2, watson->getPos().getCol(), pos.getCol());
    int r = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol() + 2) + space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol() + 2);
    int ul = space(sherlock->getPos().getRow(), pos.getRow() - 1, sherlock->getPos().getCol(), pos.getCol() - 1) + space(watson->getPos().getRow(), pos.getRow() - 1, watson->getPos().getCol(), pos.getCol() - 1);
    int dl = space(sherlock->getPos().getRow(), pos.getRow() + 1, sherlock->getPos().getCol(), pos.getCol() - 1) + space(watson->getPos().getRow(), pos.getRow() + 1, watson->getPos().getCol(), pos.getCol() - 1);
    int dr = space(sherlock->getPos().getRow(), pos.getRow() + 1, sherlock->getPos().getCol(), pos.getCol() + 1) + space(watson->getPos().getRow(), pos.getRow() + 1, watson->getPos().getCol(), pos.getCol() + 1);
    int ur = space(sherlock->getPos().getRow(), pos.getRow() - 1, sherlock->getPos().getCol(), pos.getCol() + 1) + space(watson->getPos().getRow(), pos.getRow() - 1, watson->getPos().getCol(), pos.getCol() + 1);

    string moving_rule = "O";
    int sl = -1;

    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this) && map->isValid(Position(pos.getRow() - 2, pos.getCol()), this))
    {
        if (u < sl || sl < 0)
        {
            moving_rule = "U";
            sl = u;
        }
    }

    if ((map->isValid(Position(pos.getRow() - 1, pos.getCol()), this) || map->isValid(Position(pos.getRow(), pos.getCol() + 1), this)) && map->isValid(Position(pos.getRow() - 1, pos.getCol() + 1), this))
    {
        if (ur < sl || sl < 0)
        {
            moving_rule = "UR";
            sl = ur;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this) && map->isValid(Position(pos.getRow(), pos.getCol() + 2), this))
    {
        if (r < sl || sl < 0)
        {
            moving_rule = "R";
            sl = r;
        }
    }

    if ((map->isValid(Position(pos.getRow() + 1, pos.getCol()), this) || map->isValid(Position(pos.getRow(), pos.getCol() + 1), this)) && map->isValid(Position(pos.getRow() + 1, pos.getCol() + 1), this))
    {
        if (dr < sl || sl < 0)
        {
            moving_rule = "DR";
            sl = dr;
        }
    }

    if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this) && map->isValid(Position(pos.getRow() + 2, pos.getCol()), this))
    {
        if (d < sl || sl < 0)
        {
            moving_rule = "D";
            sl = d;
        }
    }

    if ((map->isValid(Position(pos.getRow() + 1, pos.getCol()), this) || map->isValid(Position(pos.getRow(), pos.getCol() - 1), this)) && map->isValid(Position(pos.getRow() + 1, pos.getCol() - 1), this))
    {
        if (dl < sl || sl < 0)
        {
            moving_rule = "DL";
            sl = dl;
        }
    }

    if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this) && map->isValid(Position(pos.getRow(), pos.getCol() - 2), this))
    {
        if (l < sl || sl < 0)
        {
            moving_rule = "L";
            sl = l;
        }
    }

    if ((map->isValid(Position(pos.getRow() - 1, pos.getCol()), this) || map->isValid(Position(pos.getRow(), pos.getCol() - 1), this)) && map->isValid(Position(pos.getRow() - 1, pos.getCol() - 1), this))
    {
        if (ul < sl || sl < 0)
        {
            moving_rule = "UL";
            sl = ul;
        }
    }

    if (moving_rule == "U")
    {
        return Position(pos.getRow() - 2, pos.getCol());
    }
    if (moving_rule == "UR")
    {
        return Position(pos.getRow() - 1, pos.getCol() + 1);
    }
    if (moving_rule == "R")
    {
        return Position(pos.getRow(), pos.getCol() + 2);
    }
    if (moving_rule == "DR")
    {
        return Position(pos.getRow() + 1, pos.getCol() + 1);
    }
    if (moving_rule == "D")
    {
        return Position(pos.getRow() + 2, pos.getCol());
    }
    if (moving_rule == "DL")
    {
        return Position(pos.getRow() + 1, pos.getCol() - 1);
    }
    if (moving_rule == "L")
    {
        return Position(pos.getRow(), pos.getCol() - 2);
    }
    if (moving_rule == "UL")
    {
        return Position(pos.getRow() - 1, pos.getCol() - 1);
    }

    return Position::npos;
}

void RobotSW::move()
{
    Position p = this->getNextPosition();
    if (!p.isEqual(-1, -1))
    {
        int r = p.getRow(), c = p.getCol();
        pos.setRow(r);
        pos.setCol(c);
    }
}

// BaseBag
BaseBag::BaseBag(){};

BaseBag::~BaseBag(){};

StudyPinkProgram::~StudyPinkProgram(){};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////