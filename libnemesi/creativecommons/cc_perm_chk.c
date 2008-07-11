/* * 
 * This file is part of libnemesi
 *
 * Copyright (C) 2007 by LScube team <team@streaming.polito.it>
 * See AUTHORS for more details
 * 
 * libnemesi is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libnemesi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libnemesi; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *  
 * */

#include "cc.h"
#include "comm.h"

/*! \brief License permissions checking function.
 *
 * The function will check the license given as first paramenter is compatible
 * with the permissions accepted by user in <tt>Permission Mask</tt> given as
 * second parameter. Exiting, the function will return in <tt>mask</tt>
 * parameter the mask of permissions that conflict with license.
 *
 * \param license cc_license struct of license.
 *
 * \param mask pointer to permission mask used as input paramter for
 * accepted permissions by user and as return value for conflicting
 * permissions.
 */
int cc_perm_chk(cc_license * license, cc_perm_mask * mask)
{
    cc_perm_mask parsedmsk;
    return 0; //TODO: Disabled license check, should be made in a better way

    if (!license) {
        nms_printf(NMSML_DBG1, "no CC license defined\n");
        return 0;
    }
    // uriLicense parse
    if (!license->uriLicense)
        return nms_printf(NMSML_ERR,
                  "no uriLicense present: could not parse license uri\n");
    if ((cc_parse_urilicense(license->uriLicense, &parsedmsk)))
        return nms_printf(NMSML_ERR,
                  "cannot parse uriLicense (cc_prms_mask)\n");

    *((CC_BITMASK_T *) mask) =
        ~(*((CC_BITMASK_T *) mask)) & *((CC_BITMASK_T *) & parsedmsk);

    if (*((CC_BITMASK_T *) mask))
        return 1;

    return 0;
}
