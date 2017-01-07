#include "db/NoteAccessor.h"
#include "db/Helpers.h"

namespace
{
constexpr auto createNoteQuery{
    "INSERT INTO flat_mate.note (date, content, active, author_mail, flat_id) \
        VALUES($1, $2, $3, $4, $5);"};

constexpr auto removeNoteQuery{
    "DELETE FROM flat_mate.note \
        WHERE id = $1;"};

constexpr auto updateNoteQuery{
    "UPDATE flat_mate.note \
        SET content = $1, active = $2 \
        WHERE id = $3;"};

constexpr auto getNotesForFlatQuery{
    "SELECT n.id, n.date, n.content, n.active, n.author_mail, n.flat_id \
        FROM flat_mate.note n \
        WHERE n.flat_id = $1;"};

constexpr auto getNoteByIdQuery{
    "SELECT n.id, n.date, n.content, n.active, n.author_mail, n.flat_id \
        FROM flat_mate.note n \
        WHERE n.id = $1;"};
}

namespace db
{

NoteAccessorImpl::NoteAccessorImpl(std::shared_ptr<pqxx::connection_base> connection)
    : connection(connection)
{
    prepareStatements();
}

void NoteAccessorImpl::prepareStatements()
{
    connection->prepare("createNote", createNoteQuery);
    connection->prepare("removeNote", removeNoteQuery);
    connection->prepare("updateNote", updateNoteQuery);
    connection->prepare("getNotesForFlat", getNotesForFlatQuery);
    connection->prepare("getNoteById", getNoteByIdQuery);
}

void NoteAccessorImpl::create(const models::Note& note)
{
   pqxx::work w{*connection};
   const auto result = w.prepared("createNote")
                                 (note.date)
                                 (note.content)
                                 (note.active)
                                 (note.authorMail)
                                 (note.flatId).exec();
   w.commit();
   helpers::logStatementResult(result);
}

void NoteAccessorImpl::drop(const int noteId)
{
   pqxx::work w{*connection};
   const auto result = w.prepared("removeNote")
                                 (noteId).exec();
   w.commit();
   helpers::logStatementResult(result);
}

void NoteAccessorImpl::update(const models::Note& note)
{
   pqxx::work w{*connection};
   const auto result = w.prepared("updateNote")
                                 (note.content)
                                 (note.active)
                                 (note.id).exec();
   w.commit();
   helpers::logStatementResult(result);
}

std::vector<models::Note> NoteAccessorImpl::getForFlat(const int flatId)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("getNotesForFlat")
                                 (flatId).exec();

    w.commit();
    helpers::logStatementResult(result);

    std::vector<models::Note> notes;
    notes.reserve(result.size());

    std::for_each(std::cbegin(result), std::cend(result),
        [&](const pqxx::tuple row) {
            notes.push_back(models::Note{
                row["id"].as<int>(),
                row["content"].as<std::string>(),
                row["flat_id"].as<int>(),
                row["date"].as<int>(),
                row["active"].as<bool>(),
                row["author_mail"].as<std::string>()
            });
        }
    );

    return notes;
}

models::Note NoteAccessorImpl::get(const int noteId)
{
    pqxx::work w{*connection};
    const auto result = w.prepared("getNoteById")
                                 (noteId).exec();

    w.commit();
    helpers::logStatementResult(result);

    auto row = result.at(0);

    return models::Note{
        row["id"].as<int>(),
        row["content"].as<std::string>(),
        row["flat_id"].as<int>(),
        row["date"].as<int>(),
        row["active"].as<bool>(),
        row["author_mail"].as<std::string>()
    };
}

}
