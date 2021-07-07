--
-- PostgreSQL database dump
--

-- Dumped from database version 10.5
-- Dumped by pg_dump version 10.5 (Ubuntu 10.5-0ubuntu0.18.04)

-- Started on 2018-10-16 15:18:05 CEST

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 13003)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2904 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 196 (class 1259 OID 16660)
-- Name: aux; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.aux (
    user_id character varying(32),
    screen_name character varying(64),
    location_user character varying(128),
    user_created character varying(64),
    tweet_id character varying(256),
    tweet_timestamp character varying(64),
    text_tweet character varying(280),
    retweet_of character varying(16)
);


ALTER TABLE public.aux OWNER TO postgres;

--
-- TOC entry 197 (class 1259 OID 16666)
-- Name: aux2; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.aux2 (
    follower_id character varying(32),
    follower_screenname character varying(64),
    followee_id character varying(32),
    followee_screenname character varying(64)
);


ALTER TABLE public.aux2 OWNER TO postgres;

--
-- TOC entry 200 (class 1259 OID 16707)
-- Name: follow; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.follow (
    follower_id integer,
    followee_id integer
);


ALTER TABLE public.follow OWNER TO postgres;

--
-- TOC entry 199 (class 1259 OID 16697)
-- Name: tweet; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tweet (
    user_id integer,
    tweet_id integer NOT NULL,
    tweet_timestamp date,
    text_tweet character varying(280),
    retweet_of character varying(16)
);


ALTER TABLE public.tweet OWNER TO postgres;

--
-- TOC entry 198 (class 1259 OID 16692)
-- Name: user1; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.user1 (
    user_id integer NOT NULL,
    screen_name character varying(64),
    location_user character varying(128),
    user_created character varying(64)
);


ALTER TABLE public.user1 OWNER TO postgres;

--
-- TOC entry 2892 (class 0 OID 16660)
-- Dependencies: 196
-- Data for Name: aux; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.aux (user_id, screen_name, location_user, user_created, tweet_id, tweet_timestamp, text_tweet, retweet_of) FROM stdin;
100	 jack	      New Delhi	09-20-2008	201	09-20-2018	Nothing to say	\N
100	 jack	      New Delhi	09-20-2008	202	07-16-2018	Better not.	216
100	 jack	      New Delhi	09-20-2008	203	05-31-2016	Beter not.	208
101	 old_fart	Denver	10-01-2009	204	05-22-2015	Hey, here we are	\N
102	 joe_pipitone	Roma	01-01-2001	205	09-18-2018	No... we are not	\N
104	 bill_mahler	Madrid	11-11-2011	206	12-01-2017	Oops... what is this?	\N
104	 bill_mahler	Madrid	11-11-2011	207	01-05-2018	Bob, I hate you	\N
105	 trump_trumpet	Accra	03-23-2006	208	03-27-2016	Better not.	216
106	 miles_beavis	Novosibirsk	03-23-2006	209	09-17-2018	Bob, I hate you	\N
106	 miles_beavis	Novosibirsk	03-23-2006	210	04-26-2017	Everybody hates Bob	\N
107	 thelonius	Hanoi	12-25-2008	211	06-17-2015	Hey... I am Bob!	\N
107	 thelonius	Hanoi	12-25-2008	212	11-11-2017	Better not.	216
107	 thelonius	Hanoi	12-25-2008	213	08-15-2016	Who am I?	\N
108	 ann_karen	La Paz	12-01-2010	214	07-17-2015	Let't not get philosophical	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	215	10-04-1017	Oops... what is this?	206
109	 tora_tora_tora	Walla Walla	01-31-2003	216	09-19-2018	Better not.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	217	02-02-2018	Of maybe yes.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	218	09-16-2018	No, definitely not.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	219	02-02-2018	Hey... I am Bob!	211
109	 tora_tora_tora	Walla Walla	01-31-2003	220	09-17-2018	Better go to sleep.	\N
100	 jack	      New Delhi	09-20-2008	201	09-20-2018	Nothing to say	\N
100	 jack	      New Delhi	09-20-2008	202	07-16-2018	Better not.	216
100	 jack	      New Delhi	09-20-2008	203	05-31-2016	Beter not.	208
101	 old_fart	Denver	10-01-2009	204	05-22-2015	Hey, here we are	\N
102	 joe_pipitone	Roma	01-01-2001	205	09-18-2018	No... we are not	\N
104	 bill_mahler	Madrid	11-11-2011	206	12-01-2017	Oops... what is this?	\N
104	 bill_mahler	Madrid	11-11-2011	207	01-05-2018	Bob, I hate you	\N
105	 trump_trumpet	Accra	03-23-2006	208	03-27-2016	Better not.	216
106	 miles_beavis	Novosibirsk	03-23-2006	209	09-17-2018	Bob, I hate you	\N
106	 miles_beavis	Novosibirsk	03-23-2006	210	04-26-2017	Everybody hates Bob	\N
107	 thelonius	Hanoi	12-25-2008	211	06-17-2015	Hey... I am Bob!	\N
107	 thelonius	Hanoi	12-25-2008	212	11-11-2017	Better not.	216
107	 thelonius	Hanoi	12-25-2008	213	08-15-2016	Who am I?	\N
108	 ann_karen	La Paz	12-01-2010	214	07-17-2015	Let't not get philosophical	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	215	10-04-1017	Oops... what is this?	206
109	 tora_tora_tora	Walla Walla	01-31-2003	216	09-19-2018	Better not.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	217	02-02-2018	Of maybe yes.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	218	09-16-2018	No, definitely not.	\N
109	 tora_tora_tora	Walla Walla	01-31-2003	219	02-02-2018	Hey... I am Bob!	211
109	 tora_tora_tora	Walla Walla	01-31-2003	220	09-17-2018	Better go to sleep.	\N
\.


--
-- TOC entry 2893 (class 0 OID 16666)
-- Dependencies: 197
-- Data for Name: aux2; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.aux2 (follower_id, follower_screenname, followee_id, followee_screenname) FROM stdin;
100	 jack	104	 bill_mahler
100	 jack	107	 thelonius
101	 old_fart	 104	 bill_mahler     
101	 old_fart	 108	 ann_karen     
101	 old_fart	 109	 tora_tora_tora
102	 joe_pipitone 	 100	 jack
102	 joe_pipitone	 105	 trump_trumpet
102	 joe_pipitone	 107	 thelonius
103	 frank_einstein	 101	 old_fart
103	 frank_einstein	 104	 bill_mahler
105	 trump_trumpet	 101	 old_fart
105	 trump_trumpet	 102	 joe_pipitone 
107	 thelonius	 105	 trump_trumpet
108	 ann_karen	 109	 tora_tora_tora
108	 ann_karen	 105	 trump_trumpet
100	 jack	104	 bill_mahler
100	 jack	107	 thelonius
101	 old_fart	 104	 bill_mahler     
101	 old_fart	 108	 ann_karen     
101	 old_fart	 109	 tora_tora_tora
102	 joe_pipitone 	 100	 jack
102	 joe_pipitone	 105	 trump_trumpet
102	 joe_pipitone	 107	 thelonius
103	 frank_einstein	 101	 old_fart
103	 frank_einstein	 104	 bill_mahler
105	 trump_trumpet	 101	 old_fart
105	 trump_trumpet	 102	 joe_pipitone 
107	 thelonius	 105	 trump_trumpet
108	 ann_karen	 109	 tora_tora_tora
108	 ann_karen	 105	 trump_trumpet
\.


--
-- TOC entry 2896 (class 0 OID 16707)
-- Dependencies: 200
-- Data for Name: follow; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.follow (follower_id, followee_id) FROM stdin;
100	104
100	107
101	104
101	108
101	109
102	100
102	105
102	107
105	101
105	102
107	105
108	109
108	105
100	104
100	107
101	104
101	108
101	109
102	100
102	105
102	107
105	101
105	102
107	105
108	109
108	105
\.


--
-- TOC entry 2895 (class 0 OID 16697)
-- Dependencies: 199
-- Data for Name: tweet; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tweet (user_id, tweet_id, tweet_timestamp, text_tweet, retweet_of) FROM stdin;
107	212	2017-11-11	Better not.	216
109	215	1017-10-04	Oops... what is this?	206
104	206	2017-12-01	Oops... what is this?	\N
100	201	2018-09-20	Nothing to say	\N
108	214	2015-07-17	Let't not get philosophical	\N
100	203	2016-05-31	Beter not.	208
107	211	2015-06-17	Hey... I am Bob!	\N
109	220	2018-09-17	Better go to sleep.	\N
100	202	2018-07-16	Better not.	216
102	205	2018-09-18	No... we are not	\N
101	204	2015-05-22	Hey, here we are	\N
106	210	2017-04-26	Everybody hates Bob	\N
109	216	2018-09-19	Better not.	\N
109	217	2018-02-02	Of maybe yes.	\N
106	209	2018-09-17	Bob, I hate you	\N
109	218	2018-09-16	No, definitely not.	\N
107	213	2016-08-15	Who am I?	\N
109	219	2018-02-02	Hey... I am Bob!	211
105	208	2016-03-27	Better not.	216
104	207	2018-01-05	Bob, I hate you	\N
\.


--
-- TOC entry 2894 (class 0 OID 16692)
-- Dependencies: 198
-- Data for Name: user1; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.user1 (user_id, screen_name, location_user, user_created) FROM stdin;
105	 trump_trumpet	Accra	03-23-2006
107	 thelonius	Hanoi	12-25-2008
101	 old_fart	Denver	10-01-2009
104	 bill_mahler	Madrid	11-11-2011
108	 ann_karen	La Paz	12-01-2010
109	 tora_tora_tora	Walla Walla	01-31-2003
102	 joe_pipitone	Roma	01-01-2001
106	 miles_beavis	Novosibirsk	03-23-2006
100	 jack	      New Delhi	09-20-2008
\.


--
-- TOC entry 2767 (class 2606 OID 16701)
-- Name: tweet tweet_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tweet
    ADD CONSTRAINT tweet_pkey PRIMARY KEY (tweet_id);


--
-- TOC entry 2765 (class 2606 OID 16696)
-- Name: user1 user1_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.user1
    ADD CONSTRAINT user1_pkey PRIMARY KEY (user_id);


--
-- TOC entry 2770 (class 2606 OID 16715)
-- Name: follow follow_followee_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.follow
    ADD CONSTRAINT follow_followee_id_fkey FOREIGN KEY (followee_id) REFERENCES public.user1(user_id);


--
-- TOC entry 2769 (class 2606 OID 16710)
-- Name: follow follow_follower_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.follow
    ADD CONSTRAINT follow_follower_id_fkey FOREIGN KEY (follower_id) REFERENCES public.user1(user_id);


--
-- TOC entry 2768 (class 2606 OID 16702)
-- Name: tweet tweet_user_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tweet
    ADD CONSTRAINT tweet_user_id_fkey FOREIGN KEY (user_id) REFERENCES public.user1(user_id);


-- Completed on 2018-10-16 15:18:06 CEST

--
-- PostgreSQL database dump complete
--

