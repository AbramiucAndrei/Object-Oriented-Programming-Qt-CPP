#pragma once

#include "Repository.hpp"

class AbstractUndo {
public:
    /**
     * Undo the action performed by this class.
     */
    virtual void doUndo() = 0;
    virtual ~AbstractUndo() = default;
};

class UndoAdd : public AbstractUndo {
private:
    Medicament medicament;
    AbstractFarmacy &farmacy;
public:
    /**
     * Constructs an UndoAdd object.
     * @param farmacy Reference to the farmacy where the medicament was added.
     * @param medicament The medicament that was added.
     */
    UndoAdd(AbstractFarmacy &farmacy, Medicament medicament);
    void doUndo() override;
};

class UndoDelete : public AbstractUndo {
private:
    Medicament medicament;
    AbstractFarmacy &farmacy;
public:
    /**
     * Constructs an UndoDelete object.
     * @param farmacy Reference to the farmacy where the medicament was deleted.
     * @param medicament The medicament that was deleted.
     */
    UndoDelete(AbstractFarmacy &farmacy, Medicament medicament);
    void doUndo() override;
};

class UndoUpdate : public AbstractUndo {
private:
    Medicament medicament;
    AbstractFarmacy &farmacy;
public:
    /**
     * Constructs an UndoUpdate object.
     * @param farmacy Reference to the farmacy where the medicament was updated.
     * @param medicament The medicament's old state.
     */
    UndoUpdate(AbstractFarmacy &farmacy, Medicament medicament);
    void doUndo() override;
};