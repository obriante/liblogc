/*
 * deprecated.h
 *
 *  Created on: 16/ago/2013
 *      Author: kmonkey
 */

#ifndef DEPRECATED_H_
#define DEPRECATED_H_

#ifdef __GNUC__
#ifndef attribute_deprecated
#define attribute_deprecated __attribute__((deprecated))
#endif
#endif


#endif /* DEPRECATED_H_ */
