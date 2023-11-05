#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "event.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
    public:
		MyActionInitialization();
		~MyActionInitialization();
		

		//This method is invoked from G4RunManager for sequential execution
    	virtual void Build() const;
};

#endif
