/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

class Position
{
private:
    int r, c;

public:
    friend class TestStudyPink;
    static const Position npos;

    Position(int r = 0, int c = 0)
    {
        this->r = r;
        this->c = c;
    };

    Position(const string &str_pos);

    int getRow() const
    {
        return r;
    };
    int getCol() const
    {
        return c;
    };
    void setRow(int r)
    {
        this->r = r;
    };
    void setCol(int c)
    {
        this->c = c;
    };

    string str() const
    {
        return "(" + to_string(r) + "," + to_string(c) + ")";
    };

    bool isEqual(int in_r, int in_c) const
    {
        if (in_r == r and in_c == c)
            return true;
        return false;
    };

    bool isEqual(Position p) const
    {
        if (p.getRow() == r and p.getCol() == c)
            return true;
        return false;
    };
};

class MapElement
{
protected:
    ElementType type;

public:
    friend class TestStudyPink;
    MapElement();
    MapElement(ElementType in_type)
    {
        type = in_type;
    };
    virtual ~MapElement();
    virtual ElementType getType() const
    {
        return type;
    };
};

class Path : public MapElement
{
public:
    friend class TestStudyPink;
    Path() : MapElement(PATH){};
};

class Wall : public MapElement
{
public:
    friend class TestStudyPink;
    Wall() : MapElement(WALL){};
};

class FakeWall : public MapElement
{
private:
    int req_exp;

public:
    friend class TestStudyPink;
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL)
    {
        this->req_exp = in_req_exp;
    }

    int getReqExp() const
    {
        return req_exp;
    };
};

class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;

public:
    friend class TestStudyPink;
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    ~Map();
    bool isValid(const Position &pos, MovingObject *mv_obj) const;

    MapElement *getMovingElement(int r, int c)
    {
        return map[r][c];
    }
};

class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    friend class TestStudyPink;
    MovingObject();
    MovingObject(int index, const Position pos, Map *map, const string &name = "")
    {
        this->index = index;
        this->pos = pos;
        this->map = map;
        this->name = name;
    };
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const
    {
        return pos;
    };
    virtual void move() = 0;
    virtual string str() const = 0;
};

class Character : public MovingObject
{
public:
    friend class TestStudyPink;

    Character();
    Character(int index, const Position pos, Map *map, const string &name = "")
    {
        this->index = index;
        this->pos = pos;
        this->map = map;
        this->name = name;
    };

    ~Character();

    virtual void setExp(int exp) = 0;
    virtual void setHp(int hp) = 0;

    virtual string getName() = 0;
    virtual int getExp() = 0;
    virtual int getHp() = 0;
};

class Sherlock : public Character
{
private:
    int hp, exp;
    string moving_rule;

public:
    friend class TestStudyPink;

    int step = 0;

    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();

    string str() const
    {
        return "Sherlock[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }

    string getName()
    {
        return name;
    }

    int getExp()
    {
        return exp;
    }

    int getHp()
    {
        return hp;
    }

    void setExp(int exp)
    {
        this->exp = exp;
    }

    void setHp(int hp)
    {
        this->hp = hp;
    }

    Position getPos()
    {
        return pos;
    }
};

class Watson : public Character
{
private:
    int hp, exp;
    string moving_rule;

public:
    friend class TestStudyPink;

    int step = 0;

    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    Position getNextPosition();
    void move();

    string str() const
    {
        return "Watson[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
    }

    string getName()
    {
        return name;
    }

    int getExp()
    {
        return exp;
    }

    int getHp()
    {
        return hp;
    }

    void setExp(int exp)
    {
        this->exp = exp;
    }

    void setHp(int hp)
    {
        this->hp = hp;
    }

    Position getPos()
    {
        return pos;
    }
};

class Criminal : public Character
{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    friend class TestStudyPink;

    Position pre = Position(-1, -1);

    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);

    Position getNextPosition();
    void move();

    string str() const
    {
        return "Criminal[index=" + to_string(index) + ";pos=" + pos.str() + "]";
    }

    string getName()
    {
        return name;
    }

    int getHp() { return 0; };

    int getExp() { return 0; };

    void setHp(int hp) {};

    void setExp(int exp) {};

    Position getPos()
    {
        return pos;
    }

    int space(int val1, int val2, int val3, int val4)
    {
        return abs(val1 - val2) + abs(val3 - val4);
    }
};

class ArrayMovingObject
{
private:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    friend class TestStudyPink;

    ArrayMovingObject(int capacity);

    ~ArrayMovingObject();

    bool isFull() const
    {
        if (count == capacity)
            return true;
        return false;
    };

    bool add(MovingObject *mv_obj)
    {
        if (!this->isFull())
        {
            arr_mv_objs[count] = mv_obj;
            count++;
            return true;
        }
        return false;
    };

    int size() const
    {
        return count;
    };

    MovingObject *get(int index) const
    {
        return arr_mv_objs[index];
    };

    string str() const
    {
        string objs = "";
        int i = 0;
        while (i < capacity)
        {
            if (arr_mv_objs[i] != nullptr)
            {
                if (i != 0)
                {
                    objs += ";";
                }
                objs = objs + arr_mv_objs[i]->str();
            }
            i++;
        }
        return "ArrayMovingObject[count=" + to_string(count) +
               ";capacity=" + to_string(capacity) +";" +objs + "]";
    };
};

class Configuration
{
    friend class StudyPinkProgram;

private:
    int map_num_rows, map_num_cols, max_num_moving_objects, num_walls, num_fake_walls;
    int sherlock_init_hp, sherlock_init_exp, watson_init_hp, watson_init_exp, num_steps;
    string sherlock_moving_rule, watson_moving_rule;
    Position *arr_walls, *arr_fake_walls, sherlock_init_pos, watson_init_pos, criminal_init_pos;

public:
    friend class TestStudyPink;
    Configuration(const string &filepath);

    ~Configuration();

    string str() const
    {
        string wals = "", faWals = "";

        int i = 0;
        while (i < num_walls)
        {
            wals = wals + arr_walls[i].str() + ";";
            i++;
        }
        if (wals != "")
            wals.pop_back();

        i = 0;
        while (i < num_fake_walls)
        {
            faWals = faWals + arr_fake_walls[i].str() + ";";
            i++;
        }
        if (faWals != "")
            faWals.pop_back();

        return "Configuration[\nMAP_NUM_ROWS=" + to_string(map_num_rows) +
               "\nMAP_NUM_COLS=" + to_string(map_num_cols) +
               "\nMAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) +
               "\nNUM_WALLS=" + to_string(num_walls) +
               "\nARRAY_WALLS=[" + wals + "]" +
               "\nNUM_FAKE_WALLS=" + to_string(num_fake_walls) +
               "\nARRAY_FAKE_WALLS=[" + faWals + "]" +
               "\nSHERLOCK_MOVING_RULE=" + sherlock_moving_rule +
               "\nSHERLOCK_INIT_POS=" + sherlock_init_pos.str() +
               "\nSHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) +
               "\nSHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) +
               "\nWATSON_MOVING_RULE=" + watson_moving_rule +
               "\nWATSON_INIT_POS=" + watson_init_pos.str() +
               "\nWATSON_INIT_HP=" + to_string(watson_init_hp) +
               "\nWATSON_INIT_EXP=" + to_string(watson_init_exp) +
               "\nCRIMINAL_INIT_POS=" + criminal_init_pos.str() +
               "\nNUM_STEPS=" + to_string(num_steps) +
               "\n]";
    };

    int getMapNumRows()
    {
        return map_num_rows;
    }

    int getMapNumCols()
    {
        return map_num_cols;
    }

    int getMaxMoving()
    {
        return max_num_moving_objects;
    }

    int getNumWalls()
    {
        return num_walls;
    }

    int getNumFakeWalls()
    {
        return num_fake_walls;
    }

    int getSherlockHp()
    {
        return sherlock_init_hp;
    }

    int getSherExp()
    {
        return sherlock_init_exp;
    }

    int getWatsonHp()
    {
        return watson_init_hp;
    }

    int getWatsonExp()
    {
        return watson_init_exp;
    }

    int getNumSteps()
    {
        return num_steps;
    }

    Position *getArrWalls()
    {
        return arr_walls;
    }

    Position *getArrFakeWalls()
    {
        return arr_fake_walls;
    }

    Position getSherlockPos()
    {
        return sherlock_init_pos;
    }

    Position getWatsonPos()
    {
        return watson_init_pos;
    }

    Position getCriminalPos()
    {
        return criminal_init_pos;
    }

    string getSMR()
    {
        return sherlock_moving_rule;
    }

    string getWMR()
    {
        return watson_moving_rule;
    }
};

class Robot : public MovingObject
{
protected:
    RobotType robot_type;
    BaseItem *item;

public:
    friend class TestStudyPink;

    Criminal *criminal;
    Robot();
    Robot(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal);
    ~Robot();
    void setBaseItem(BaseItem *bi)
    {
        item = bi;
    }
};

class RobotC : public Robot
{
public:
    friend class TestStudyPink;

    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal);

    Position getNextPosition()
    {
        return criminal->pre;
    }

    void move()
    {
        if (!this->getNextPosition().isEqual(-1, -1))
        {
            pos.setRow(this->getNextPosition().getRow());
            pos.setCol(this->getNextPosition().getCol());
        }
    }

    int getDistance(MovingObject *mo)
    {
        return abs(pos.getRow() - mo->getCurrentPosition().getRow()) + abs(pos.getCol() - mo->getCurrentPosition().getCol());
    }

    string str() const
    {
        return "Robot[pos=" + pos.str() + ";type=" + name + ";dist=" + "]";
    }
};

class RobotS : public Robot
{
public:
    friend class TestStudyPink;

    Sherlock *sherlock;

    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock);

    Position getNextPosition();
    void move();

    int getDistance()
    {
        return abs(pos.getRow() - sherlock->getPos().getRow()) + abs(pos.getCol() - sherlock->getPos().getCol());
    }

    string str() const
    {
        int dist = abs(pos.getRow() - sherlock->getPos().getRow()) + abs(pos.getCol() - sherlock->getPos().getCol());
        return "Robot[pos=" + pos.str() + ";type=" + name + ";dist=" + to_string(dist) + "]";
    }

    int space(int a, int b, int x, int y)
    {
        return abs(a - b) + abs(x - y);
    }
};

class RobotW : public Robot
{
public:
    friend class TestStudyPink;

    Watson *watson;

    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);

    Position getNextPosition();
    void move();

    int getDistance()
    {
        return abs(pos.getRow() - watson->getPos().getRow()) + abs(pos.getCol() - watson->getPos().getCol());
    }

    string str() const
    {
        int dist = abs(pos.getRow() - watson->getPos().getRow()) + abs(pos.getCol() - watson->getPos().getCol());
        return "Robot[pos=" + pos.str() + ";type=" + name + ";dist=" + to_string(dist) + "]";
    }

    int space(int a, int b, int x, int y)
    {
        return abs(a - b) + abs(x - y);
    }
};

class RobotSW : public Robot
{
public:
    friend class TestStudyPink;

    Sherlock *sherlock;
    Watson *watson;

    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);

    Position getNextPosition();
    void move();

    int getDistance()
    {
        return abs(pos.getRow() - watson->getPos().getRow()) + abs(pos.getCol() - watson->getPos().getCol()) +
               abs(pos.getRow() - sherlock->getPos().getRow()) + abs(pos.getCol() - sherlock->getPos().getCol());
    }

    string str() const
    {
        int dist = abs(pos.getRow() - watson->getPos().getRow()) + abs(pos.getCol() - watson->getPos().getCol()) + abs(pos.getRow() - sherlock->getPos().getRow()) + abs(pos.getCol() - sherlock->getPos().getCol());
        return "Robot[pos=" + pos.str() + ";type=" + name + ";dist=" + to_string(dist) + "]";
    }

    int space(int a, int b, int x, int y)
    {
        return abs(a - b) + abs(x - y);
    }
};

class BaseItem
{
public:
    friend class TestStudyPink;

    string name;
    ItemType type;

    BaseItem(){};

    virtual bool canUse(Character *character, Robot *robot = nullptr) = 0;
    virtual void use(Character *character, Robot *robot = nullptr) = 0;
};

class MagicBook : public BaseItem
{
public:
    friend class TestStudyPink;

    MagicBook()
    {
        name = "MagicBook";
        type = MAGIC_BOOK;
    };

    bool canUse(Character *character, Robot *robot)
    {
        if (character->getExp() < 350)
        {
            return true;
        }
        return false;
    };
    void use(Character *character, Robot *robot)
    {
        int exp = (character->getExp()) + (character->getExp()) * 0.25;
        character->setExp(exp);
    };
};

class EnergyDrink : public BaseItem
{
public:
    friend class TestStudyPink;

    EnergyDrink()
    {
        name = "EnergyDrink";
        type = ENERGY_DRINK;
    }

    bool canUse(Character *character, Robot *robot)
    {
        if (character->getHp() <= 100)
        {
            return true;
        }
        return false;
    };
    void use(Character *character, Robot *robot) {
    };
};

class FirstAid : public BaseItem
{
public:
    friend class TestStudyPink;

    FirstAid()
    {
        name = "FirstAid";
        type = FIRST_AID;
    }

    bool canUse(Character *character, Robot *robot)
    {
        if (character->getHp() <= 100 || character->getExp() <= 350)
        {
            return true;
        }
        return false;
    };
    void use(Character *character, Robot *robot)
    {
        int hp = (character->getHp()) * (1 + 0.5);
        character->setHp(hp);
    };
};

class ExcemptionCard : public BaseItem
{
public:
    friend class TestStudyPink;

    ExcemptionCard()
    {
        name = "ExcemptionCard";
        type = EXCEMPTION_CARD;
    }

    bool canUse(Character *character, Robot *robot)
    {
        if (character->getName() == "Sherlock" && character->getHp() % 2 == 1 && robot != nullptr)
        {
            return true;
        }
        return false;
    };
    void use(Character *character, Robot *robot)
    {
        int hp = (character->getHp()) * 1.5;
        character->setHp(hp);
    };
};

class PassingCard : public BaseItem
{
public:
    friend class TestStudyPink;

    string challenge;

    PassingCard(string str)
    {
        challenge = str;
        name = "PassingCard";
        type = PASSING_CARD;
    }

    bool canUse(Character *character, Robot *robot)
    {
        if (robot != nullptr)
        {
            return true;
        }
        return false;
    };
    void use(Character *character, Robot *robot)
    {
        int hp = (character->getHp()) * 1.25;
        character->setHp(hp);
    };
};

struct NodeBaseItem
{
    BaseItem *item;
    NodeBaseItem *next;
};

class BaseBag
{
protected:
    int capacity;
    int count;
    Character *obj;
    NodeBaseItem *head;

public:
    friend class TestStudyPink;

    BaseBag();
    ~BaseBag();

    virtual bool insert(BaseItem *item) = 0;

    virtual BaseItem *get() = 0;
    virtual BaseItem *get(ItemType itemType) = 0;

    virtual string str() const = 0;
};

class SherlockBag : public BaseBag
{
public:
    friend class TestStudyPink;

    SherlockBag(Sherlock *sherlock)
    {
        capacity = 13;
        count = 0;
        obj = sherlock;
        head = nullptr;
    };

    bool insert(BaseItem *item)
    {
        if (count < capacity)
        {
            NodeBaseItem *n = new NodeBaseItem;
            n->item = item;
            n->next = head;
            head = n;
            count++;
            return true;
        }
        return false;
    };

    BaseItem *get()
    {
        NodeBaseItem *p = head, *pre = head;
        int i = 0;
        while (i < count)
        {
            if (p->item->canUse(obj, nullptr))
            {
                count--;

                if (p == head)
                {
                    head = head->next;
                    return p->item;
                }
                if (pre == head)
                {
                    head->next = p->next;
                    return p->item;
                }
                pre->next = p->next;
                p->next = head->next;
                head->next = pre->next;
                pre->next = head;
                head = p->next;
                return p->item;
            }
            pre = p;
            p = p->next;
            i++;
        }

        return nullptr;
    };

    BaseItem *get(ItemType itemType)
    {
        NodeBaseItem *p = head, *pre = head;

        int i = 0;
        while (i < count)
        {
            if (p->item->type == itemType)
            {
                count--;

                if (p == head)
                {
                    head = head->next;
                    return p->item;
                }
                if (pre == head)
                {
                    head->next = p->next;
                    return p->item;
                }
                pre->next = p->next;
                p->next = head->next;
                head->next = pre->next;
                pre->next = head;
                head = p->next;
                return p->item;
            }
            pre = p;
            p = p->next;
            i++;
        }

        return nullptr;
    };

    string str() const
    {
        string item = ";";
        NodeBaseItem *p = head;
        int i = 0;
        while (i < count)
        {
            item = item + p->item->name + ",";
            p = p->next;
            i++;
        }
        if (item.length() > 0)
            item.pop_back();
        return "Bag[count=" + to_string(count) + item + "]";
    };
};

class WatsonBag : public BaseBag
{
public:
    friend class TestStudyPink;

    WatsonBag(Watson *watson)
    {
        capacity = 15;
        count = 0;
        obj = watson;
        head = nullptr;
    };

    bool insert(BaseItem *item)
    {
        if (count < capacity)
        {
            NodeBaseItem *n = new NodeBaseItem;
            n->item = item;
            n->next = head;
            head = n;
            count++;
            return true;
        }
        return false;
    };

    BaseItem *get()
    {
        NodeBaseItem *p = head, *pre = head;
        int i = 0;
        while (i < count)
        {
            if (p->item->canUse(obj, nullptr))
            {
                count--;

                if (p == head)
                {
                    head = head->next;
                    return p->item;
                }
                if (pre == head)
                {
                    head->next = p->next;
                    return p->item;
                }
                pre->next = p->next;
                p->next = head->next;
                head->next = pre->next;
                pre->next = head;
                head = p->next;
                return p->item;
            }
            pre = p;
            p = p->next;
            i++;
        }

        return nullptr;
    };

    BaseItem *get(ItemType itemType)
    {
        NodeBaseItem *p = head, *pre = head;

        int i = 0;
        while (i < count)
        {
            if (p->item->type == itemType)
            {
                count--;

                if (p == head)
                {
                    head = head->next;
                    return p->item;
                }
                if (pre == head)
                {
                    head->next = p->next;
                    return p->item;
                }
                pre->next = p->next;
                p->next = head->next;
                head->next = pre->next;
                pre->next = head;
                head = p->next;
                return p->item;
            }
            pre = p;
            p = p->next;
            i++;
        }

        return nullptr;
    };

    string str() const
    {
        string items = ";";
        NodeBaseItem *node = head;
        int i = 0;
        while (i < count)
        {
            items = items + node->item->name + ",";
            node = node->next;
            i++;
        }
        if (items != ";")
            items.pop_back();
        return "Bag[count=" + to_string(count) + items + "]";
    };
};

class StudyPinkProgram
{
private:
    Configuration *config;

    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;

    Map *map;
    ArrayMovingObject *arr_mv_objs;

public:
    BaseBag *sherlock_bag, *watson_bag;

    int num_steps = 0;
    StudyPinkProgram(const string &config_file_path)
    {
        Configuration *config = new Configuration(config_file_path);

        this->map = new Map(config->getMapNumRows(), config->getMapNumCols(), config->getNumWalls(), config->getArrWalls(), config->getNumFakeWalls(), config->getArrFakeWalls());

        this->sherlock = new Sherlock(1, config->getSMR(), config->getSherlockPos(), map, config->getSherlockHp(), config->getSherExp());
        this->watson = new Watson(2, config->getWMR(), config->getWatsonPos(), map, config->getWatsonHp(), config->getWatsonExp());
        this->criminal = new Criminal(0, config->getCriminalPos(), map, sherlock, watson);

        this->arr_mv_objs = new ArrayMovingObject(config->getMaxMoving());
        this->sherlock_bag = new SherlockBag(sherlock);
        this->watson_bag = new WatsonBag(watson);

        this->arr_mv_objs->add(sherlock);
        this->arr_mv_objs->add(watson);
        this->arr_mv_objs->add(criminal);

        num_steps = config->num_steps;
    };

    bool isStop() const
    {
        if (sherlock->getHp() == 0 || watson->getHp() == 0 || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            return true;
        }
        return false;
    };

    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose)
    {
        int id = 0;
        while (id < num_steps)
        {
            if (id == 2)
            {
                RobotC *rc = new RobotC(3, criminal->getCurrentPosition(), map, criminal);
                int p = CalculateTotal(rc->getCurrentPosition());
                SetRobotItem(rc, p);
                arr_mv_objs->add(rc);
            }
            else if ((id + 1) % 3 == 0)
            {
                Position pos = criminal->getCurrentPosition();
                int str1 = space(sherlock->getPos().getRow(), pos.getRow(), sherlock->getPos().getCol(), pos.getCol());
                int str2 = space(watson->getPos().getRow(), pos.getRow(), watson->getPos().getCol(), pos.getCol());

                Robot *robot = nullptr;
                if (str1 > str2)
                {
                    robot = new RobotS(2 + (id + 1) / 3, criminal->getCurrentPosition(), map, criminal, sherlock);
                }
                else if (str1 < str2)
                {
                    robot = new RobotW(2 + (id + 1) / 3, criminal->getCurrentPosition(), map, criminal, watson);
                }
                else if (str1 == str2)
                {
                    robot = new RobotSW(2 + (id + 1) / 3, criminal->getCurrentPosition(), map, criminal, sherlock, watson);
                }
                int p = CalculateTotal(robot->getCurrentPosition());
                SetRobotItem(robot, p);
                arr_mv_objs->add(robot);
            }

            int i = 0;
            while (i < arr_mv_objs->size())
            {
                arr_mv_objs->get(i)->move();
                if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition()))
                {
                    BaseItem *bi = sherlock_bag->get(PASSING_CARD);
                    while (bi != nullptr)
                    {
                        watson_bag->insert(bi);
                        bi = sherlock_bag->get(PASSING_CARD);
                    }

                    bi = watson_bag->get(EXCEMPTION_CARD);
                    while (bi != nullptr)
                    {
                        sherlock_bag->insert(bi);
                        bi = watson_bag->get(EXCEMPTION_CARD);
                    }
                }

                if (isStop())
                {
                    printStep(id);
                    break;
                }
                if (verbose)
                {
                    printStep(id);
                }
                i++;
            }
            id++;
        }

        printResult();
    }

    ~StudyPinkProgram();

    int CalculateTotal(Position pos)
    {
        int p = pos.getRow() * pos.getCol(), s = 0;

        while (p / 10 > 0)
        {
            s += p % 10;
            p = p / 10;

            if (s + p % 10 >= 10)
                return s;
        }

        if (s + p >= 10)
            return s;

        return s + p;
    }

    void SetRobotItem(Robot *Rb, int p)
    {
        BaseItem *item = nullptr;
        if (0 <= p && p <= 1)
        {
            item = new MagicBook();
            Rb->setBaseItem(item);
        }
        else if (2 <= p && p <= 3)
        {
            item = new EnergyDrink();
            Rb->setBaseItem(item);
        }
        else if (4 <= p && p <= 5)
        {
            item = new FirstAid();
            Rb->setBaseItem(item);
        }
        else if (6 <= p && p <= 7)
        {
            item = new ExcemptionCard();
            Rb->setBaseItem(item);
        }
        else if (8 <= p && p <= 9)
        {
            Position rbp = Rb->getCurrentPosition();
            int l = (rbp.getRow() * 11 + rbp.getCol()) % 4;
            string typ = ChooseRobot(l);
            item = new PassingCard(typ);
            Rb->setBaseItem(item);
        }
    }

    string ChooseRobot(int l)
    {
        if (l = 0)
        {
            return "RobotS";
        }
        else if (l = 1)
        {
            return "RobotC";
        }
        else if (l = 2)
        {
            return "RobotSW";
        }
        else if (l = 3)
        {
            return "all";
        }
    }

    int space(int a, int b, int c, int d)
    {
        return abs(a - b) + abs(c - d);
    }
};
#endif