#ifndef _IMPORTEXCEPTION_HPP_
#define _IMPORTEXCEPTION_HPP_

typedef std::vector<Enemy*> EnemeyVec;
typedef std::vector<EnemeyVec> EnemyTable;

class ImportException {
    public:
        ImportException(){}
        ImportException(std::string _message){ message = _message; }
        std::string what(){ return message; }
        void set(std::string _message){ message = _message; }
        void play(Window* window){ window->play_sound_effect("Music/error.wav"); }
    private:
        std::string message;
};

#endif