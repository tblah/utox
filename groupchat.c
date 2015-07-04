void callback_group_invite(Tox *tox, int32_t fid, const uint8_t *data, uint16_t length, void *UNUSED(userdata)){
    int gid = -1;
    if (type == TOX_GROUPCHAT_TYPE_TEXT) {
        gid = tox_join_groupchat(tox, fid, data, length);
    } else if (type == TOX_GROUPCHAT_TYPE_AV) {
        gid = toxav_join_av_groupchat(tox, fid, data, length, &callback_av_group_audio, NULL);
    }

    if(gid != -1) {
        postmessage(GROUP_ADD, gid, 0, tox);
    }

    debug("Group Invite (%i,f:%i) type %u\n", gid, fid, type);
}

void callback_group_message(Tox *tox, int gid, int pid, const uint8_t *message, uint16_t length, void *UNUSED(userdata)){
    postmessage(GROUP_MESSAGE, gid, 0, copy_groupmessage(tox, message, length, MSG_TYPE_TEXT, gid, pid));

    debug("Group Message (%u, %u): %.*s\n", gid, pid, length, message);
}

void callback_group_action(Tox *tox, int gid, int pid, const uint8_t *action, uint16_t length, void *UNUSED(userdata)){
    postmessage(GROUP_MESSAGE, gid, 0, copy_groupmessage(tox, action, length, MSG_TYPE_ACTION_TEXT, gid, pid));

    debug("Group Action (%u, %u): %.*s\n", gid, pid, length, action);
}

void callback_group_peerlist_update(Tox *tox, int gid, void *UNUSED(userdata)){
    switch(change) {
    case TOX_CHAT_CHANGE_PEER_ADD: {
        postmessage(GROUP_PEER_ADD, gid, pid, tox);
        break;
    }

    case TOX_CHAT_CHANGE_PEER_DEL: {
        postmessage(GROUP_PEER_DEL, gid, pid, tox);
        break;
    }

    case TOX_CHAT_CHANGE_PEER_NAME: {
        uint8_t name[TOX_MAX_NAME_LENGTH];
        int len = tox_group_peername(tox, gid, pid, name);

        len = utf8_validate(name, len);

        uint8_t *data = malloc(len + 1);
        data[0] = len;
        memcpy(data + 1, name, len);

        postmessage(GROUP_PEER_NAME, gid, pid, data);
        break;
    }
    }
    debug("Group Namelist Change (%u, %u): %u\n", gid, pid, change);
}

void callback_group_topic_update(Tox *tox, int gid, int pid, const uint8_t *topic, uint8_t length, void *UNUSED(userdata)){
    length = utf8_validate(topic, length);
    if (!length)
        return;

    uint8_t *copy_title = malloc(length);
    if (!copy_title)
        return;

    memcpy(copy_title, topic, length);
    postmessage(GROUP_TITLE, gid, length, copy_title);

    debug("Group Title (%u, %u): %.*s\n", gid, pid, length, topic);
}

        tox_callback_group_private_message(Tox *tox, void (*function)(Tox *m, int, uint32_t, const uint8_t *, uint16_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, const uint8_t *message, uint16_t length, void *userdata)

        /* Set the callback for group moderation events.
         *
         */
        tox_callback_group_moderation(Tox *tox, void (*function)(Tox *m, int, uint32_t, uint32_t, TOX_GROUP_MOD_EVENT, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t source_peernum, uint32_t target_peernum, TOX_GROUP_MOD_EVENT type, void *userdata)

        /* Set the callback for group peer nickname changes.
         *
         */
        tox_callback_group_nick_change(Tox *tox, void (*function)(Tox *m, int, uint32_t, const uint8_t *, uint16_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, const uint8_t *newnick, uint16_t length, void *userdata)

        /* Set the callback for group peer status changes.
         *
         */
        tox_callback_group_status_change(Tox *tox, void (*function)(Tox *m, int, uint32_t, uint8_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, uint8_t status, void *userdata)

        /* Set the callback for group topic changes.
         *
         */
        tox_callback_group_topic_change(Tox *tox, void (*function)(Tox *m, int, uint32_t, const uint8_t *, uint16_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, const uint8_t *topic, uint16_t length, void *userdata)

        /* Set the callback for group peer join alert. This callback must not be
         * relied on for updating the client's peer list (use tox_callback_group_peerlist_update).
         *
         */
        tox_callback_group_peer_join(Tox *tox, void (*function)(Tox *m, int, uint32_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, void *userdata)

        /* Set the callback for group peer exit alert. This callback must not be
         * relied on for updating the client's peer list (use tox_callback_group_peerlist_update).
         *
         */
        tox_callback_group_peer_exit(Tox *tox, void (*function)(Tox *m, int, uint32_t, const uint8_t *, uint16_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint32_t peernumber, const uint8_t *partmessage, uint16_t length, void *userdata)

        /* Set the callback for group self join.
         *
         */
        tox_callback_group_self_join(Tox *tox, void (*function)(Tox *m, int, void *), void *userdata);
function(Tox *m, int groupnumber, void *userdata)

        /* Set the callback for when your join attempt is rejected where type is one of TOX_GROUP_JOIN_REJECTED.
         *
         */
        tox_callback_group_rejected(Tox *tox, void (*function)(Tox *m, int, uint8_t, void *), void *userdata);
function(Tox *m, int groupnumber, uint8_t type, void *userdata)

