#include "MyUserControl.h"
#include "PostRepository.h"

using namespace QQ;

/*void MyUserControl::LoadAndDisplayPosts()
{
    List<Post^>^ posts = PostRepository::LoadAllPosts();
    List<BlogPostCard^>^ cards = gcnew List<BlogPostCard^>();

    for each (Post ^ post in posts) {
        cards->Add(gcnew BlogPostCard(post));
    }

    DisplayPosts(cards);
}*/

/*void MyUserControl::DisplayPosts(List<BlogPostCard^>^ cards)
{
    mainflow->Controls->Clear();
    for each (BlogPostCard ^ card in cards) {
        mainflow->Controls->Add(card);
    }
}*/

System::Collections::Generic::List<Post^>^ QQ::MyUserControl::LoadAllPosts()
{
    throw gcnew System::NotImplementedException();
    // TODO: вставьте здесь оператор return
}
