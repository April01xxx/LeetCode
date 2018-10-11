/**
 * Table: Person
 * +-------------+---------+
 * | Column Name | Type    |
 * +-------------+---------+
 * | PersonId    | int     |
 * | FirstName   | varchar |
 * | LastName    | varchar |
 * +-------------+---------+
 * PersonId is the primary key column for this table.
 *
 * Table: Address
 * +-------------+---------+
 * | Column Name | Type    |
 * +-------------+---------+
 * | AddressId   | int     |
 * | PersonId    | int     |
 * | City        | varchar |
 * | State       | varchar |
 * +-------------+---------+
 * AddressId is the primary key column for this table.
 *
 * Write a SQL query for a report that provides the following information for
 * each person in the Person table, regardless if there is an address for each
 * of those people:
 * FirstName, LastName, City, State
 *
 * 关联查询,可能Address表中没有该人的信息,用外连接就可以了.下面是用Oracle语法写的.
 */
select FirstName, LastName, City, State
from Person p, Address a
where p.PersonId = a.PersonId(+);