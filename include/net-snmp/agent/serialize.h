/* The serialized helper merely calls its clients multiple times for a
 * given request set, so they don't have to loop through the requests
 * themselves.
 */

#ifdef __cplusplus
extern "C" {
#endif

netsnmp_mib_handler *get_serialize_handler(void);
int register_serialize(netsnmp_handler_registration *reginfo);
void init_serialize(void);
    
Netsnmp_Node_Handler serialize_helper_handler;

#ifdef __cplusplus
};
#endif
