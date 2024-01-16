####################
Server Configuration
####################

The following Docker-Compose file is used to define all the necessary server components:

.. literalinclude:: ../docker/compose.yml
    :language: yaml
    :linenos:

To initialize the server, run ``docker-compose -f docker/compose.yml up``

To stop the server, run ``docker-compose -f docker/compose.yml down``

To stop the server and delete all persistent volumes, run ``docker-compose -f docker/compose.yml down -v``

==========
Components
==========

+----------------+--------------------------------+--------------------------------------+----------------+----------------------------------------------------------------------------+
| Container Name | Image                          | Volumes                              | Port Mapping   | Environment Variables                                                      | 
+================+================================+======================================+================+============================================================================+
| postgres       | ``postgres:latest``            | ``pgdata:/var/lib/postgresql/data``  | ``5432:5432``  | | ``POSTGRES_USER``: admin                                                 |
|                |                                |                                      |                | | ``POSTGRES_PASSWORD``: $POSTGRES_PASSWORD                                |
+----------------+--------------------------------+--------------------------------------+----------------+----------------------------------------------------------------------------+
| pgadmin        | ``dpage/pgadmin4:latest``      |                                      | ``4000:80``    | | ``PGADMIN_DEFAULT_EMAIL``: aquaclean@wright.edu                          |
|                |                                |                                      |                | | ``PGADMIN_DEFAULT_PASSWORD``: $PGADMIN_DEFAULT_PASSWORD                  |
+----------------+--------------------------------+--------------------------------------+----------------+----------------------------------------------------------------------------+
| postgrest      | ``postgrest/postgrest:latest`` |                                      | ``3000:3000``  | ``PGRST_DB_URI``: postgres://admin:${POSTGRES_PASSWORD}@192.168.1.100:5432 |
|                |                                |                                      |                |                                                                            |
+----------------+--------------------------------+--------------------------------------+----------------+----------------------------------------------------------------------------+
| grafana        | ``grafana/grafana-oss:latest`` | ``grafana-storage:/var/lib/grafana`` | ``8000:5432``  |                                                                            |
|                |                                |                                      |                |                                                                            |
+----------------+--------------------------------+--------------------------------------+----------------+----------------------------------------------------------------------------+
