/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "opfile_x.h"

bool_t
xdr_AggStanza (XDR *xdrs, AggStanza *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nomeStanza, MAX_STRING,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->tipo))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Utente (XDR *xdrs, Utente *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nome, MAX_STRING,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Stanza (XDR *xdrs, Stanza *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nomeStanza, MAX_STRING,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->tipo))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->utente, K,
		sizeof (Utente), (xdrproc_t) xdr_Utente))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_ListaStanze (XDR *xdrs, ListaStanze *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->ris))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->elenco, N,
		sizeof (Stanza), (xdrproc_t) xdr_Stanza))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_AggUtente (XDR *xdrs, AggUtente *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nomeStanza, MAX_STRING,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->nomeUtente, MAX_STRING,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}