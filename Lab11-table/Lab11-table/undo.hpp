#include "Repository.hpp"
//interfata
class ActiuneUndo {

public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga:public ActiuneUndo {
	Repository& repo;
	Medicament adaugat;
public:
	UndoAdauga(Repository& repoo,const Medicament& added):repo{repoo},adaugat{added}{}

	void doUndo() override{
		repo.deleteMedicament(adaugat.getDenumire());
	}
};

class UndoSterge :public ActiuneUndo {
	Repository& repo;
	Medicament sters;
public:
	UndoSterge(Repository& repoo, const Medicament& deleted) :repo{ repoo }, sters{ deleted } {}
	void doUndo() override {
		repo.addMedicament(sters);
	}
};

class UndoModifica :public ActiuneUndo {
	Repository& repo;
	Medicament nou;
	Medicament vechi;
public:
	UndoModifica(Repository &rpo,const Medicament &_new,const Medicament &old)
		:repo{ rpo }, vechi{ old }, nou{ _new } {}

	void doUndo() override {
		

		repo.updateMedicament(nou.getDenumire(),vechi);
	}
};