#include "CommService.h"
#include "CommRepository.h"

using namespace QQ;

bool CommService::AddNewComment(
    Post^ post,
    User^ author,
    String^ text,
    DateTime date,
    bool isReply,
    int serialOtvet,
    int idOtvUser,
    int parentCommId
) {
    if (String::IsNullOrWhiteSpace(text)) return false;

    return CommRepository::AddComment(
        post->ID,
        author->ID,
        idOtvUser,
        text,
        date,
        isReply,
        serialOtvet,
        parentCommId
    );
}
