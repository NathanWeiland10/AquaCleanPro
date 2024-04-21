#pragma once

class Motor{
    public:
        Motor();
        
        Motor(int pinNumE, int pinNumM);

        void stop();

        void turnForward();

        void turnBackward();
    private:
        int pinE;
        int pinM;
};