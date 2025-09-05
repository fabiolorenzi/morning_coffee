#include "TutorialDialog.h"

TutorialDialog::TutorialDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Tutorial");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setPlainText(
        "Welcome to Morning Coffee!\n\n"
        "This application helps you track updates from your favorite sources:\n"
        "- Blogs\n"
        "- YouTube channels\n"
        "- Patreon pages\n\n"

        "Setup Instructions:\n"
        "1. Download the application for your operating system from the GitHub page.\n"
        "2. In the application folder, create a file named .env\n"
        "3. Inside .env, add your YouTube API key like this:\n"
        "   YOUTUBE_API_KEY=<your_api_key>\n\n"

        "Main Menu Overview:\n"
        "- Add new source: Add a blog, YouTube channel, or Patreon page.\n"
        "- Manage sources: Update or remove existing sources.\n"
        "- Exit: Close the application.\n"
        "- View summary: Get an overview of which sources have updates.\n"
        "- View new blogs: See updated blogs (double-click to open in browser).\n"
        "- View new videos: See updated YouTube channels (double-click to open).\n"
        "- View new patreons: See updated Patreon pages (double-click to open).\n"
        "- About: Learn more about the software.\n"
        "- Tutorial: Open this guide.\n"
        "- Visit GitHub page: Open the project’s GitHub page in your browser.\n\n"

        "Tips:\n"
        "- Double-clicking an entry in the update lists will open it directly in your browser.\n"
        "- Keep your .env file safe. Without a valid YouTube API key, YouTube updates won’t work.\n\n"

        "Enjoy staying up-to-date without checking each page manually!\n"
    );

    layout->addWidget(textEdit);

    QPushButton *closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    resize(600, 400);
}