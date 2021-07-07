--AUTORES: ANDRES MENA GODINO Y JUAN MORENO DIEZ
--GRUPO: INGLES, 1291
--QUERY INVENTED 1:
create view tweets_2018 as
select *
from tweet 
where tweet_timestamp >= '2018-01-01 00:00:00' and tweet_timestamp <= '2018-12-31 00:00:00'

create view most_twitters as
select user_id, count(*) as number_tweets
from tweets_2018
group by user_id
order number_tweets

create view max_number_tweets_2018 as
select max(number_tweets) as maximum_tweets
from most_twitters

create view id_most_tweeter as
select user_id 
from most_twitters as m1, max_number_tweets_2018 as m2
where m1.number_tweets=m2.maximum_tweets

select screen_name
from user1 as u1, id_most_tweeter as u2
where u1.user_id=u2.user_id



--QUERY INVENTED 2:
create view spanish_users as
select *
from user1
where location_user like 'Espaa' or location_user like 'Spain';

create view followers_of_spanish as
select user_id, count(follower_id) as num_followers
from spanish_users, follow
where spanish_users.user_id=followee_id
group by spanish_users.user_id;

create view max_num_followers as
select max(num_followers) as max_num_followers
from followers_of_spanish;

create view most_popular_spanish_id as
select user_id
from max_num_followers as a1, followers_of_spanish as a2
where a1.max_num_followers=a2.num_followers;

create view ids_followees_spanish as
select follower_id
from most_popular_spanish_id, follow
where followee_id=most_popular_spanish_id.user_id;

select screen_name
from user1, ids_followees_spanish
where user1.user_id=ids_followees_spanish.follower_id
