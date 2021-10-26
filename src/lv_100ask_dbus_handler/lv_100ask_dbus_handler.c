/**
 * @file lv_100ask_dbus_handler.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_modules.h"

#if LV_USE_100ASK_DBUS_HANDLER

#include <stdio.h>
#include <signal.h>
#include <dbus/dbus.h>
#include "lv_100ask_dbus_handler.h"

//static DBusConnection *g_connection;

static void check_and_abort(DBusError *error);
static void respond_to_introspect(DBusConnection *connection, DBusMessage *request);
static void respond_to_states(DBusConnection *connection, DBusMessage *request);
static DBusHandlerResult tutorial_messages(DBusConnection *connection, DBusMessage *message, void *user_data);



static void respond_to_states(DBusConnection *connection, DBusMessage *request) {
    DBusMessage *reply;
    DBusError error;
    int states = 1;

    dbus_error_init(&error);

    // 获取参数数值
    dbus_message_get_args(request, &error,
                  DBUS_TYPE_INT32, &states,
                  DBUS_TYPE_INVALID);
    if (dbus_error_is_set(&error)) {
        reply = dbus_message_new_error(request, "wrong_arguments", "Illegal arguments to Sum");
        dbus_connection_send(connection, reply, NULL);
        dbus_message_unref(reply);
        return;
    }

#if 0
    reply = dbus_message_new_method_return(request);
    dbus_message_append_args(reply,
                 DBUS_TYPE_INVALID);
    dbus_connection_send(connection, reply, NULL);
    dbus_message_unref(reply);
#endif

}



static void check_and_abort(DBusError *error) {
    if (dbus_error_is_set(error)) {
        puts(error->message);
        abort();
    }
}

// TODO : property
static void respond_to_introspect(DBusConnection *connection, DBusMessage *request) {
    DBusMessage *reply;

    const char *introspection_data =
        " <!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" "
        "\"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">"
        " <!-- dbus-sharp 0.8.1 -->"
        " <node>"
        "   <interface name=\"org.freedesktop.DBus.Introspectable\">"
        "     <method name=\"Introspect\">"
        "       <arg name=\"data\" direction=\"out\" type=\"s\" />"
        "     </method>"
        "   </interface>"
        "   <interface name=\"net.ask100.lvgl.test\">"
        "     <method name=\"states\">"
        "       <arg name=\"states\" direction=\"in\" type=\"i\" />"
        "     </method>"
        "     <property name=\"Status\" type=\"u\" access=\"readwrite\"/>"
        "   </interface>"
        " </node>";

    reply = dbus_message_new_method_return(request);
    dbus_message_append_args(reply,
                 DBUS_TYPE_STRING, &introspection_data,
                 DBUS_TYPE_INVALID);
    dbus_connection_send(connection, reply, NULL);
    dbus_message_unref(reply);
}


static DBusHandlerResult tutorial_messages(DBusConnection *connection, DBusMessage *message, void *user_data) {
    const char *interface_name = dbus_message_get_interface(message);
    const char *member_name = dbus_message_get_member(message);
     
    if (0==strcmp("org.freedesktop.DBus.Introspectable", interface_name) &&
        0==strcmp("Introspect", member_name)) {
 
        respond_to_introspect(connection, message);
        return DBUS_HANDLER_RESULT_HANDLED;
    } else if (0==strcmp("net.ask100.lvgl.test", interface_name) &&
           0==strcmp("states", member_name)) {
         
        respond_to_states(connection, message);
        return DBUS_HANDLER_RESULT_HANDLED;
    }  else {
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }
}



static void *dbus_dispatch_thread_func(void *pvoid)
{
    DBusConnection * connection = (DBusConnection *)pvoid;
    while(1)
    {
        // 从DBus队列读取消息，阻塞直到消息可用，然后将消息分派给感兴趣的对象，等待时间为0则为无限等待。
        dbus_connection_read_write_dispatch(connection, 1000);
    }
}

#if 1
void dbus_method_call(const char *destination, const char *path, const char *iface, const char *method, const int state, const int pid)
{
    DBusConnection *connection;
    DBusError error;
    DBusMessage *message;

    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);

    if ( dbus_error_is_set(&error) )
    {
        printf("Error getting dbus connection: %s\n",error.message);
        dbus_error_free(&error);
        dbus_connection_unref(connection);
        return 0;
    }
    
    printf("\n\ndbus_method_call:\n");
    printf("%s, %s, %s, %s, %d, %d\n\n", destination, path, iface, method, state, pid);

    message = dbus_message_new_method_call(destination, path, iface, method);
    if(message == NULL) {
        printf("[error] Message NULL!!!");
        return;
    }

    /* Append the argument to the message */
    dbus_message_append_args(message, DBUS_TYPE_INT32, &state, DBUS_TYPE_INT32, &pid, DBUS_TYPE_INVALID);

    dbus_message_set_no_reply(message, TRUE);  // We don't want to receive a reply
    if( !dbus_connection_send(connection, message, NULL)){
        printf("Out of Memory/n");
        exit(1);
    }

    //printf("11111111111111 dbus_connection_unref\n");
    //dbus_connection_flush(connection);
    //printf("22222222222222 dbus_connection_unref\n");
    dbus_message_unref(message);
    dbus_connection_unref(connection);
    
    //printf("state:%d\n", state);
    //if (state == 1) exit(0);

}
#endif



void lv_100ask_dbus_handler_init(void)
{
    DBusConnection *onnection;
    DBusError error;
    DBusObjectPathVTable vtable;
    int ret;
    pthread_t tid;
 
    dbus_error_init(&error);
    onnection = dbus_bus_get(DBUS_BUS_SESSION, &error);  // 每个连接到DBus 总线的应用程序都有一个唯一的名称。
    check_and_abort(&error);
 
    // 如果应用程序想要被其他应用程序访问，它必须获得一个“众所周知”的名称，这里是获得“众所周知”的名称
    dbus_bus_request_name(onnection, "net.ask100.lvgl.test", 0, &error);
    check_and_abort(&error);

    //dbus_connection_flush(onnection);
 
    vtable.message_function = tutorial_messages;
    vtable.unregister_function = NULL;
     
    // 尝试注册一个新的对象为当前应用程序
    dbus_connection_try_register_object_path(onnection,
                         "/net/ask100/lvgl/test",
                         &vtable,
                         NULL,
                         &error);
    check_and_abort(&error);

    ret = pthread_create(&tid, NULL, dbus_dispatch_thread_func, onnection);
}




#endif
