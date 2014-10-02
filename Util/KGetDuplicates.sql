/*$RCSfile: KGetDuplicates.sql,v $: Transact-SQL script file
  $Revision: 1.2 $ $Date: 2014/10/02 16:48:15 $
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

  Example:
      exec sp_GetDuplicates 'MyTableName', 'ColumnName1, ColumnName2, ColumnName3'
 */
CREATE PROCEDURE sp_GetDuplicates
  @sTable varchar(255), --Name of the source table
  @sFields varchar(1024) --list of the columns to be browsed for duplicate records
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
 *$Log: KGetDuplicates.sql,v $
 *Revision 1.2  2014/10/02 16:48:15  ddarko
 *comment
 *
 *Revision 1.1  2008/06/02 21:28:17  ddarko
 *Created
 *
 */
