
#ifndef UNTITLED7_POLITICIANINTERFACE_H
#define UNTITLED7_POLITICIANINTERFACE_H
//IObserver
class PoliticianInterface {
public:
    virtual ~PoliticianInterface(){};
    // the function should update each observer
    virtual void updateChairman(PoliticianInterface *politician) = 0;

};

#endif //UNTITLED7_POLITICIANINTERFACE_H
