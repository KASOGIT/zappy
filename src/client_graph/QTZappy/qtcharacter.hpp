#ifndef QTCHARACTER_HPP
#define QTCHARACTER_HPP

class QTCharacter {
public:
    QTCharacter(int x, int z, int o, int id, std::string teamName){
            _x = x;
            _z = z;
            _id = id;
            _o = o;
            _teamName = teamName;
            _lvl = 1;
            _resource[0] = 0;
            _resource[1] = 0;
            _resource[2] = 0;
            _resource[3] = 0;
            _resource[4] = 0;
            _resource[5] = 0;
            _resource[6] = 0;
        }
    ~QTCharacter(){}

    int     getLvl() {
        return (_lvl);
    }

    int    getResource(int resource)  {
        return (_resource[resource]);
    }

    void    setResource(int resource, int nb) {
        _resource[resource] = nb;
    }

    void    updateLvl() {
        _lvl += 1;
    }

    void    updatePos(int x, int z, int O) {
        _x = x;
        _z = z;
        _o = O;
    }

    int     getId() const {
        return _id;
    }

    std::string     getTeamName() const {
        return _teamName;
    }

    int     getX() const {
        return _x;
    }

    int     getZ() const {
        return _z;
    }
private:
    std::map<int, int>           _resource;
    int                                   _x;
    int                                   _z;
    int                                   _id;
    int                                   _o;
    int                                   _lvl;
    std::string                       _teamName;
};

#endif // QTCHARACTER_HPP
