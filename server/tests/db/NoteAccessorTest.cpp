#include "gtest/gtest.h"

#include "db/PostgreConfig.h"
#include "db/DatabaseInitializer.h"
#include "db/NoteAccessor.h"

#include "models/User.h"

using namespace ::testing;

class NoteAccessorTest : public Test
{
public:
    void SetUp()
    {
        initializeDatabase();
    }

    void initializeDatabase()
    {
        db::DatabaseInitializer dbInitializer{config::db_opts};
        dbInitializer.init();
        dbInitializer.fill();
    }

protected:
    models::User newUser{"test@gmail.com", "Testy", "Test", "TestMe", "pass"};
    models::User existingUser{"czeslavo@gmail.com", "czeslavo", "Grzegorz", "Burzynski", "pass"};

    models::Note newNote{126, "Content of the note", 1, 21551512, true, "czeslavo@gmail.com"};
    models::Note existingNote{1, "", 1, 1463313600, true, "czeslavo@gmail.com"};

    std::shared_ptr<pqxx::connection>
        connection{std::make_shared<pqxx::connection>(config::db_opts)};

    db::NoteAccessorImpl sut{connection};
};

TEST_F(NoteAccessorTest, shouldAddNote)
{
    sut.create(newNote);
}

TEST_F(NoteAccessorTest, shouldRemoveNote)
{
    sut.drop(existingNote.id);
}

TEST_F(NoteAccessorTest, shouldNotRemoveExistingNote)
{
    sut.drop(newNote.id);
}

TEST_F(NoteAccessorTest, shouldUpdateNote)
{
    existingNote.content = "changed content";
    sut.update(existingNote);
}

TEST_F(NoteAccessorTest, shouldGetNotesForFlat)
{
    const auto notes = sut.getForFlat(1);
    EXPECT_EQ(notes.size(), 3);
}

TEST_F(NoteAccessorTest, shouldGetNoteById)
{
    const auto note = sut.get(1);
    EXPECT_EQ(note.id, 1);
}
