#pragma once

#include <memory>
#include <pqxx/pqxx>
#include <vector>

#include "models/Note.h"

namespace db
{

class NoteAccessor
{
public:
    virtual ~NoteAccessor() = default;

    virtual void create(const models::Note& note) = 0;
    virtual void drop(const int noteId) = 0;
    virtual void update(const models::Note& note) = 0;
    virtual std::vector<models::Note> getForFlat(const int flatId) = 0;
    virtual models::Note get(const int noteId) = 0;
};

class NoteAccessorImpl : public NoteAccessor
{
public:
    NoteAccessorImpl(std::shared_ptr<pqxx::connection_base> connection);

    void create(const models::Note& note) override;
    void drop(const int noteId) override;
    void update(const models::Note& note) override;
    std::vector<models::Note> getForFlat(const int flatId) override;
    models::Note get(const int noteId) override;

private:
    void prepareStatements();
    std::shared_ptr<pqxx::connection_base> connection;

};
}
