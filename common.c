

int el_errorToString(int error, chari **string)
{
    switch ( error ) 
    {
        case EL_ERR_NONE:
            *string = "EL_ERR_NONE";
            break;
        case EL_ERR_FAILED:
            *string = "EL_ERR_FAILED";
            break;
        case EL_ERR_MEM:
            *string = "EL_ERR_MEM";
            break;
        case EL_ERR_PARAM:
            *string = "EL_ERR_PARAM";
            break;

        default:
            *string = "UNKNOWN";
            return EL_ERR_PARAM;
    }
    return EL_ERR_NONE; 
}



