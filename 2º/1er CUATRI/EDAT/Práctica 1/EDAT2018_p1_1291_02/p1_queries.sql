--AUTORES: ANDRES MENA GODINO Y JUAN MORENO DIEZ
--GRUPO: INGLES, 1291

--QUERY A)
select tweet_timestamp, text_tweet
from tweet 
order by tweet_timestamp 
asc  limit 1

select tweet_timestamp, text_tweet
from tweet 
order by tweet_timestamp 
desc  limit 1

--QUERY B)
create view num_followers as
select followee_id, count(follower_id) as number_followers
from follow 
group by followee_id

select avg (number_followers) as density
from num_followers


--QUERY D)

create view followed1 as
select follower_id as follower
from follow
where followee_id='760839'

create view followed2 as
select follower_id as follower
from follow
where followee_id='811737'

select f1 as Common_followers_ids
from followed1 as f1,followed2 as f2
where f1.follower=f2.follower


--QUERY E)
create view followers_user1 as
select followee_id as followee
from follow
where follower_id='811737'

create view followers_user2 as
select followee_id as followee
from follow
where follower_id='769919'

select f1 as both_follow_ids
from followers_user1 as f1,followers_user2 as f2
where f1.followee=f2.followee

--QUERY G)
create view number_of_followers as
select followee_id, count (*) as num_followers
from follow
group by followee_id

create view most_number_followers as
select max(num_followers) as most_followed
from number_of_followers

create view id_most_followed as
select followee_id
from most_number_followers f1, number_of_followers f2
where f1.most_followed=f2.num_followers

select screen_name
from user1 as u1, id_most_followed as u2
where u1.user_id=u2.followee_id


--QUERY I)
create view id_of_most_rt as
select user_id, count(*)
from tweet 
group by user_id
order by count desc

select screen_name
from id_of_most_rt natural join user1
limit 1
