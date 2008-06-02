/*$RCSfile: KIsRecDuplicate.sql,v $: Transact-SQL script file
  $Revision: 1.1 $ $Date: 2008/06/02 21:20:49 $
  $Author: ddarko $

  List all duplicate records from a database table.
 */

-- ============================================================================
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'sp_GetDuplicates' AND xtype = 'P')
  DROP PROC sp_GetDuplicates
PRINT 'Create sp_GetDuplicates stored procedure'
GO

/* =============================================================================
  Returns all duplicate records from a table.
 */
CREATE PROCEDURE sp_GetDuplicates
  @sTable varchar(255),
  @sFields varchar(1024)
AS
DECLARE @sSql AS varchar(5000)
  /*Create the query request*/
SET @sSql = 'SELECT ' + @sFields + ', ' +
            '        COUNT(*) AS nNumOccurrences' +
            ' FROM ' + @sTable +
            ' GROUP BY ' + @sFields +
            ' HAVING ( COUNT(*) > 1 )';
PRINT @sSql

EXEC (@sSql);
GO


/*------------------------------------------------------------------------------
 *$Log: KIsRecDuplicate.sql,v $
 *Revision 1.1  2008/06/02 21:20:49  ddarko
 **** empty log message ***
 *
 */
