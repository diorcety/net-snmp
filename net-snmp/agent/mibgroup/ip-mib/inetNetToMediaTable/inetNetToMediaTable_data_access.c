/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.12 $ of : mfd-data-access.m2c,v $ 
 *
 * $Id$
 */
/*
 * standard Net-SNMP includes 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*
 * include our parent header 
 */
#include "inetNetToMediaTable.h"


#include "inetNetToMediaTable_data_access.h"

/** @defgroup data_access data_access: Routines to access data
 *
 * These routines are used to locate the data used to satisfy
 * requests.
 * 
 * @{
 */
/**********************************************************************
 **********************************************************************
 ***
 *** Table inetNetToMediaTable
 ***
 **********************************************************************
 **********************************************************************/
/*
 * inetNetToMediaTable is subid 35 of ip.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.4.35, length: 8
 */

/**
 * initialization for inetNetToMediaTable data access
 *
 * This function is called during startup to allow you to
 * allocate any resources you need for the data table.
 *
 * @param inetNetToMediaTable_reg
 *        Pointer to inetNetToMediaTable_registration
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : unrecoverable error.
 */
int
inetNetToMediaTable_init_data(inetNetToMediaTable_registration_ptr
                              inetNetToMediaTable_reg)
{
    DEBUGMSGTL(("verbose:inetNetToMediaTable:inetNetToMediaTable_init_data", "called\n"));

    /*
     * TODO:303:o: Initialize inetNetToMediaTable data.
     */

    return MFD_SUCCESS;
}                               /* inetNetToMediaTable_init_data */

/**
 * container-cached overview
 *
 */

/***********************************************************************
 *
 * cache
 *
 ***********************************************************************/
/**
 * container initialization
 *
 * @param container_ptr_ptr A pointer to a container pointer. If you
 *        create a custom container, use this parameter to return it
 *        to the MFD helper. If set to NULL, the MFD helper will
 *        allocate a container for you.
 * @param  cache A pointer to a cache structure. You can set the timeout
 *         and other cache flags using this pointer.
 *
 *  This function is called at startup to allow you to customize certain
 *  aspects of the access method. For the most part, it is for advanced
 *  users. The default code should suffice for most cases. If no custom
 *  container is allocated, the MFD code will create one for your.
 *
 *  This is also the place to set up cache behavior. The default, to
 *  simply set the cache timeout, will work well with the default
 *  container. If you are using a custom container, you may want to
 *  look at the cache helper documentation to see if there are any
 *  flags you want to set.
 *
 * @remark
 *  This would also be a good place to do any initialization needed
 *  for you data source. For example, opening a connection to another
 *  process that will supply the data, opening a database, etc.
 */
void
inetNetToMediaTable_container_init(netsnmp_container ** container_ptr_ptr,
                                   netsnmp_cache * cache)
{
    DEBUGMSGTL(("verbose:inetNetToMediaTable:inetNetToMediaTable_container_init", "called\n"));

    if ((NULL == cache) || (NULL == container_ptr_ptr)) {
        snmp_log(LOG_ERR,
                 "bad params to inetNetToMediaTable_container_init\n");
        return;
    }

    /*
     * For advanced users, you can use a custom container. If you
     * do not create one, one will be created for you.
     */
    *container_ptr_ptr = NULL;

    /*
     * TODO:345:A: Set up inetNetToMediaTable cache properties.
     *
     * Also for advanced users, you can set parameters for the
     * cache. Do not change the magic pointer, as it is used
     * by the MFD helper.
     */
    cache->timeout = INETNETTOMEDIATABLE_CACHE_TIMEOUT; /* seconds */
}                               /* inetNetToMediaTable_container_init */

/**
 * check entry for update
 *
 */
static void
_snarf_arp_entry(netsnmp_arp_entry * arp_entry,
                 netsnmp_container * container)
{
    inetNetToMediaTable_rowreq_ctx *rowreq_ctx;

    DEBUGTRACE;

    netsnmp_assert(NULL != arp_entry);
    netsnmp_assert(NULL != container);

    /*
     * allocate an row context and set the index(es), then add it to
     * the container
     */
    rowreq_ctx = inetNetToMediaTable_allocate_rowreq_ctx(arp_entry);
    if ((NULL != rowreq_ctx) &&
        (MFD_SUCCESS == inetNetToMediaTable_indexes_set
         (rowreq_ctx, rowreq_ctx->data->if_index,
          rowreq_ctx->data->arp_ipaddress_len,
          rowreq_ctx->data->arp_ipaddress,
          rowreq_ctx->data->arp_ipaddress_len))) {
        CONTAINER_INSERT(container, rowreq_ctx);
    } else {
        if (rowreq_ctx) {
            snmp_log(LOG_ERR, "error setting index while loading "
                     "inetNetToMediaTable cache.\n");
            inetNetToMediaTable_release_rowreq_ctx(rowreq_ctx);
        } else
            netsnmp_access_arp_entry_free(arp_entry);
    }
}

/**
 * load cache data
 *
 * TODO:350:M: Implement inetNetToMediaTable cache load
 *
 * @param container container to which items should be inserted
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_RESOURCE_UNAVAILABLE : Can't access data source
 * @retval MFD_ERROR                : other error.
 *
 *  This function is called to cache the index(es) (and data, optionally)
 *  for the every row in the data set.
 *
 * @remark
 *  While loading the cache, the only important thing is the indexes.
 *  If access to your data is cheap/fast (e.g. you have a pointer to a
 *  structure in memory), it would make sense to update the data here.
 *  If, however, the accessing the data invovles more work (e.g. parsing
 *  some other existing data, or peforming calculations to derive the data),
 *  then you can limit yourself to setting the indexes and saving any
 *  information you will need later. Then use the saved information in
 *  inetNetToMediaTable_row_prep() for populating data.
 *
 * @note
 *  If you need consistency between rows (like you want statistics
 *  for each row to be from the same time frame), you should set all
 *  data here.
 *
 */
int
inetNetToMediaTable_cache_load(netsnmp_container * container)
{
    netsnmp_container *arp_container;

    DEBUGMSGTL(("verbose:inetNetToMediaTable:inetNetToMediaTable_cache_load", "called\n"));

    /*
     * TODO:351:M: |-> Load/update data in the inetNetToMediaTable container.
     * loop over your inetNetToMediaTable data, allocate a rowreq context,
     * set the index(es) [and data, optionally] and insert into
     * the container.
     */
    arp_container =
        netsnmp_access_arp_container_load(NULL,
                                          NETSNMP_ACCESS_ARP_LOAD_NOFLAGS);
    if (NULL == arp_container)
        return MFD_RESOURCE_UNAVAILABLE;        /* msg already logged */

    /*
     * we just got a fresh copy of data. snarf data
     */
    CONTAINER_FOR_EACH(arp_container,
                       (netsnmp_container_obj_func *) _snarf_arp_entry,
                       container);

    /*
     * free the container. we've either claimed each entry, or released it,
     * so the access function doesn't need to clear the container.
     */
    netsnmp_access_arp_container_free(arp_container,
                                      NETSNMP_ACCESS_ARP_FREE_DONT_CLEAR);

    DEBUGMSGT(("verbose:inetNetToMediaTable:inetNetToMediaTable_cache_load", "%d records\n", CONTAINER_SIZE(container)));

    return MFD_SUCCESS;
}                               /* inetNetToMediaTable_cache_load */

/**
 * cache clean up
 *
 * @param container container with all current items
 *
 *  This optional callback is called prior to all
 *  item's being removed from the container. If you
 *  need to do any processing before that, do it here.
 *
 * @note
 *  The MFD helper will take care of releasing all the row contexts.
 *
 */
void
inetNetToMediaTable_cache_free(netsnmp_container * container)
{
    DEBUGMSGTL(("verbose:inetNetToMediaTable:inetNetToMediaTable_cache_free", "called\n"));

    /*
     * TODO:380:M: Free inetNetToMediaTable cache.
     */
}                               /* inetNetToMediaTable_cache_free */

/**
 * prepare row for processing.
 *
 *  When the agent has located the row for a request, this function is
 *  called to prepare the row for processing. If you fully populated
 *  the data context during the index setup phase, you may not need to
 *  do anything.
 *
 * @param rowreq_ctx pointer to a context.
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 */
int
inetNetToMediaTable_row_prep(inetNetToMediaTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL(("verbose:inetNetToMediaTable:inetNetToMediaTable_row_prep",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:390:o: Prepare row for request.
     * If populating row data was delayed, this is the place to
     * fill in the row for this request.
     */

    return MFD_SUCCESS;
}                               /* inetNetToMediaTable_row_prep */

/** @} */
